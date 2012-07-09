CC = gcc
CXX = g++
CFLAGS = -O3 -Werror -Wall -Wextra
CXXFLAGS = -O3 -Werror -Wall -Wextra

.PHONY: compile
compile: head-unit.o asserts.o head-unit-cpp.o
	ar rcs libheadunit.a head-unit.o asserts.o head-unit-cpp.o

.PHONY: install
install:
	./install.sh

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.a
