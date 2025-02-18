CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework
AR = ar
ARFLAGS = rcs

all: PhotoMagic test PhotoMagic.a

PhotoMagic: main.o PhotoMagic.o FibLFSR.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

test: test.o FibLFSR.o PhotoMagic.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

PhotoMagic.a: PhotoMagic.o FibLFSR.o
	$(AR) $(ARFLAGS) $@ $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o PhotoMagic test PhotoMagic.a

lint:
	cpplint *.cpp *.hpp


.PHONY: all clean lint
