#include <dirent.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Структура заметки
struct Note {
  string title;    // Название заметки
  string content;  // Текст заметки
};

void writeStructVectorToFile(const vector<Note>& vec, const string& filename);

vector<Note> readStructVectorFromFile(const string& filename) {
  ifstream file(filename);
  vector<Note> vec;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      size_t pos = line.find(",");
      if (pos != string::npos) {
        string title = line.substr(0, pos);
        string content = line.substr(pos + 1);
        vec.push_back({title, content});
      } else {
        cout << endl << "Разделитель не найден!" << endl;
      }
    }
    file.close();
  } else {
    cout << endl << "Не удалось открыть файл!" << endl;
  }
  return vec;
}

// Функция для создания новой заметки
void createNote() {
  Note note;
  vector<Note> notes = readStructVectorFromFile("base.txt");
  cout << "Введите название заметки: ";
  getline(cin, note.title);
  cout << "Введите содержание заметки: ";
  getline(cin, note.content);
  notes.push_back(note);
  writeStructVectorToFile(notes, "base.txt");
  cout << endl << "Заметка успешно создана!" << endl;
}

// Функция для редактирования заметки
void editNote() {
  vector<Note> notes = readStructVectorFromFile("base.txt");
  cout << "Выберете заметку для редактирования: " << endl;
  int noteNum;
  cin >> noteNum;
  cin.ignore();
  if (static_cast<vector<Note>::size_type>(noteNum) <= notes.size()) {
    cout << "Введите новое содержание: ";
    getline(cin, notes[noteNum - 1].content);
    writeStructVectorToFile(notes, "base.txt");
    cout << endl << "Заметка успешно отредактирована!" << endl;
  } else {
    cout << endl << "Заметки с таким номером не существует!" << endl;
  }
}

// Функция для вывода списка заметок
void listNotes() {
  cout << "Список заметок: " << endl;
  vector<Note> notesVector = readStructVectorFromFile("base.txt");
  for (vector<Note>::size_type i = 0; i < notesVector.size(); i++) {
    cout << i + 1 << ". " << notesVector[i].title << endl;
  }
}

// Функция для вывода заметки
void viewNote() {
  int noteNum;
  cout << "Введите номер заметки для просмотра: ";
  cin >> noteNum;
  vector<Note> notes = readStructVectorFromFile("base.txt");
  if (static_cast<vector<Note>::size_type>(noteNum) <= notes.size()) {
    cout << endl;
    cout << "Название заметки: " + notes[noteNum - 1].title << endl;
    cout << "Содержание заметки: " + notes[noteNum - 1].content << endl;
  } else {
    cout << endl << "Заметки с таким номером не существует!" << endl;
  }
}

//Функция для удаления заметки
void deleteNote() {
  int noteNum;
  vector<Note> notesVector = readStructVectorFromFile("base.txt");
  cout << "Введите номер заметки для удаления:" << endl;
  cin >> noteNum;
  notesVector.erase(notesVector.begin() + noteNum - 1);
  writeStructVectorToFile(notesVector, "base.txt");
}

// Функция записи вектора в файл
void writeStructVectorToFile(const vector<Note>& vec, const string& filename) {
  ofstream file(filename);
  if (file.is_open()) {
    for (const auto& s : vec) {
      file << s.title << "," << s.content << "\n";
    }
    file.close();
  } else {
    cout << "Не удалось открыть файл!" << endl;
  }
}

// Главная функция
int main() {
  int choice;
  do {
    cout << endl;
    cout << "Выбор действия:" << endl;
    cout << "1. Создать заметку" << endl;
    cout << "2. Редактировать заметку" << endl;
    cout << "3. Показать список заметок" << endl;
    cout << "4. Показать содержание заметки" << endl;
    cout << "5. Удалить заметку" << endl;
    cout << "6. Выход" << endl;
    cin >> choice;
    cin.clear();
    cin.ignore();
    switch (choice) {
      case 1:
        createNote();
        break;
      case 2:
        editNote();
        break;
      case 3:
        listNotes();
        break;
      case 4:
        viewNote();
        break;
      case 5:
        deleteNote();
        break;
      case 6:
        break;
      default: {
        cout << "Неверное действие. Повт6орите ввод." << endl;
      }
    }
  } while (choice != 6);
  return 0;
}