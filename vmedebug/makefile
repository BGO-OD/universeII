CC          = g++ -Wall -g
LN	    = g++ -Wall
INCLUDE	    = ../vmelib
LIBS	    = -L../vmelib -lvmelib

vmedebug: vmedebug.o
	$(LN) vmedebug.o $(LIBS) -o vmedebug

vmedebug.o: vmedebug.cpp
	$(CC) -I$(INCLUDE) vmedebug.cpp -c -o vmedebug.o

clean:
	rm -f *.o vmedebug
