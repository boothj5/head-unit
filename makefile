CC=gcc

make-headunit: 
	$(CC) -Wall -o libheadunit.a -c head-unit.c

install: make-headunit
	cp libheadunit.a ~/lib
	cp head-unit.h ~/include

clean:
	rm -f *.o
	rm -f *.a
	rm -f ~/lib/libheadunit.a
	rm -f ~/include/head-unit.h	
