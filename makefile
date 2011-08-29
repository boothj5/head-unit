CC=gcc
CFLAGS =-Werror -Wall -Wextra

make-headunit: head-unit.o 
	ar rcs libheadunit.a head-unit.o

install: make-headunit
	cp libheadunit.a ~/lib
	cp head-unit.h ~/include

clean:
	rm -f *.o
	rm -f *.a
	rm -f ~/lib/libheadunit.a
	rm -f ~/include/head-unit.h	
