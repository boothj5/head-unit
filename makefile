CC=g++
CFLAGS=-Werror -Wall -Wextra
CXXFLAGS=-Werror -Wall -Wextra

compile: head-unit.o head-unit-cpp.o
	ar rcs libheadunit.a head-unit.o
	ar rcs libheadunitcpp.a head-unit-cpp.o

install: compile
	cp libheadunit.a ~/lib
	cp head-unit.h ~/include
	cp libheadunitcpp.a ~/lib
	cp head-unit-cpp.h ~/include

clean:
	rm -f *.o
	rm -f *.a
	rm -f ~/lib/libheadunit.a
	rm -f ~/lib/libheadunitcpp.a
	rm -f ~/include/head-unit.h	
	rm -f ~/include/head-unit-cpp.h	
