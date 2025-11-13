CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
TARGET = chess
SOURCES = main.cpp chess.cpp
HEADERS = chess.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
