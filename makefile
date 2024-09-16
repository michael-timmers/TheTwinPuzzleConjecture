COMPILER=clang++
CPPFLAGS= -std=c++20
LDFLAGS=

APP_NAME=PuzzleConjecture
EXECUTABLE=bin/$(APP_NAME)

SRC = src
SOURCES=$(wildcard $(SRC)/*.cpp $(SRC)/**/*.cpp)
HPPSOURCES = $(wildcard $(SRC)/*.hpp $(SRC)/*/*.hpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(LDFLAGS) -o $@ $^

%.o: %.cpp $(HPPSOURCES)
	$(COMPILER) $(CPPFLAGS) -c $< -o $@

all: $(EXECUTABLE) makefile

clean:
	rm -fr $(EXECUTABLE) $(OBJECTS) $(LIBRARY) $(LIBHPP)

run:
	./$(EXECUTABLE)

.PHONY: all clean run