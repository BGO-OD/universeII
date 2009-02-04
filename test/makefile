CC          = g++ -Wall -g -O2
LN	    = g++ -Wall
INCLUDE	    = ../vmelib
LIBS	    = -L../vmelib -lvmelib 
PROGS       = test_simple test_mmap test_dma test_llist test_mbx

%.o:%.cpp
	$(CC) -I$(INCLUDE) -c $<

all: $(PROGS)

test_simple: test_simple.o
	$(LN) test_simple.o $(LIBS) -o test_simple

test_mmap: test_mmap.o
	$(LN) test_mmap.o $(LIBS) -o test_mmap

test_dma: test_dma.o
	$(LN) test_dma.o $(LIBS) -o test_dma

test_llist: test_llist.o
	$(LN) test_llist.o $(LIBS) -o test_llist

test_mbx: test_mbx.o
	$(LN) test_mbx.o $(LIBS) -o test_mbx

clean:
	rm -f *.o $(PROGS)
