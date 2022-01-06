#
# Makefile for CS 70 IntList Assignment
#
# As usual, you can build this software by typing
#
#     make
#

all: intlist-test

intlist-test: intlist-test.o intlist.o
	clang++ -o intlist-test intlist-test.o intlist.o -L/usr/lib/cs70lib -l testinglogger

intlist.o: intlist.cpp intlist.hpp
	clang++ -c -g -std=c++17 -Wall -Wextra -pedantic intlist.cpp

intlist-test.o: intlist-test.cpp intlist.hpp
	clang++ -c -g -std=c++17 -Wall -Wextra -pedantic intlist-test.cpp

clean:
	rm -rf intlist-test *.o *.dSYM
