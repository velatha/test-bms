# Makefile for Monopoly Game

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
TARGET = monopoly
TEST_TARGET = test_monopoly
SOURCES = main.cpp Game.cpp Board.cpp Player.cpp Space.cpp Dice.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Game.h Board.h Player.h Space.h Dice.h

# Shared object files (excluding main.o)
GAME_OBJECTS = Game.o Board.o Player.o Space.o Dice.o

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(TEST_TARGET): test_monopoly.cpp $(GAME_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test_monopoly.cpp $(GAME_OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)
