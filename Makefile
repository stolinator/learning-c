SHELL=/bin/bash # so brace expansion works as expected
CFLAGS=-Wall -g

ex19:
	cc -Wall -g -DNDEBUG ex19.c -o ex19

ex22:
	cc -Wall -g -DNDEBUG -c -o ex22.o ex22.c
	cc -Wall -g -DNDEBUG ex22_main.c ex22.o -o ex22_main

clean:
	rm -f ex{1..17}
	rm -f db.dat
	rm -f database
