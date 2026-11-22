all:ex22_main

ex22-t: ex22-test.c
	cc -Wall -g ex22-test.c -o ex22-test

ex22_main: ex22_main.c ex22.o
	cc -Wall -g -DNDEBUG   -c -o ex22.o ex22.c
	cc -Wall -g -DNDEBUG    ex22_main.c ex22.o   -o ex22_main
clean:
	rm -f ex22_main ex22.o ex22-test
