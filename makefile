CC=g++
CXX=g++
CFLAGS=-Werror -Wall -Wextra
CXXFLAGS=-Werror -Wall -Wextra

compile: head-unit.o asserts.o head-unit-cpp.o
	ar rcs libheadunit.a head-unit.o asserts.o head-unit-cpp.o

install: compile
	cp libheadunit.a ~/lib
	cp head-unit.h ~/include

clean:
	rm -f *.o
	rm -f *.a
