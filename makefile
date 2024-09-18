COMPILER=clang++
CPPFLAGS= -std=c++17
LDFLAGS= -v

APP_NAME=PuzzleConjecture
EXECUTABLE=bin/$(APP_NAME)

SRC = src
SOURCES=$(wildcard $(SRC)/*.cpp)
HPPSOURCES = $(wildcard $(SRC)/*.hpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(LDFLAGS) -o $@ $^

%.o: %.cpp $(HPPSOURCES)
	$(COMPILER) $(CPPFLAGS) -c $< -o $@

all: $(EXECUTABLE) makefile

clean:
	rm -fr $(EXECUTABLE) $(OBJECTS)

run:
	./$(EXECUTABLE)

.PHONY: all clean run