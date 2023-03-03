SHELL=/bin/bash # so brace expansion works as expected
CFLAGS=-Wall -g

ex19:
	cc -Wall -g -DNDEBUG ex19.c -o ex19

clean:
	rm -f ex{1..17}
	rm -f db.dat
	rm -f database
