CC=g++
CXX=g++
CFLAGS=-Werror -Wall -Wextra
CXXFLAGS=-Werror -Wall -Wextra

compile: head-unit.o asserts.o head-unit-cpp.o asserts-cpp.o
	ar rcs libheadunit.a head-unit.o asserts.o
	ar rcs libheadunitcpp.a head-unit-cpp.o asserts-cpp.o

install: compile
	cp libheadunit.a ~/lib
	cp head-unit.h ~/include
	cp libheadunitcpp.a ~/lib
	cp head-unit-cpp.h ~/include

clean:
	rm -f *.o
	rm -f *.a
