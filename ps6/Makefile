CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Werror
LDFLAGS = -lboost_unit_test_framework

all: TextWriter TextWriter.a test

TextWriter: TextWriter.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TextWriter.a: RandWriter.o
	ar rcs $@ $^

test: test.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o TextWriter TextWriter.a test

.PHONY: all clean lint