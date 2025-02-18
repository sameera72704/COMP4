CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_unit_test_framework

all: Sokoban Sokoban.a test

Sokoban: main.o Sokoban.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

test: test.o Sokoban.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS)

Sokoban.a: Sokoban.o
	ar rcs $@ $^

main.o: main.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $<

Sokoban.o: Sokoban.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $<

test.o: test.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $<

lint:
	cpplint *.cpp *.hpp

clean:
	rm -f *.o Sokoban Sokoban.a test

.PHONY: all lint clean test
