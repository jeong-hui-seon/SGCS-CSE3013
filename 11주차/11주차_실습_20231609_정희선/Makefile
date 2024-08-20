# Makefile to compile C++ program with C++11 standard

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11
TARGET = maze
SRC = 20231609.cpp

# Make commands
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
