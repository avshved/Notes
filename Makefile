CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic

SRC=notes.cpp
OBJ=$(SRC:.cpp=.o)
EXE=notes

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)