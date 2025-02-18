CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Werror -pedantic
LDFLAGS = -lsfml-system

all: EDistance test EDistance.a

EDistance: main.o EDistance.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: test.o EDistance.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lboost_unit_test_framework

EDistance.a: EDistance.o
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o EDistance test EDistance.a

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

.PHONY: all clean lint