CLFAGS=-Wall -g
all:ex19

test: ex19
	bash test-ex19.sh

object.o: object.c
	cc $(CLFAGS) -c object.c -o object.o

ex19: ex19.c object.o
	cc $(CLFAGS) ex19.c object.o -o ex19
clean:
	rm -f ex19 object.o
