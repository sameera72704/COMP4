CXX = g++
CXXFLAGS = -std=c++17 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: Penta

Penta: main.o penta.o
	$(CXX) main.o penta.o -o Penta $(SFMLFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

penta.o: penta.cpp penta.hpp
	$(CXX) $(CXXFLAGS) -c penta.cpp

clean:
	rm -f *.o Penta

lint:
	cpplint *.cpp *.hpp

