# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRC = main.cpp FibLFSR.cpp
TEST_SRC = test.cpp FibLFSR.cpp

# Executable names
TARGET = lfsr_program
TEST_TARGET = test

# Build the main program
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Build the test executable
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET) -lboost_unit_test_framework

# Clean up generated files
clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
