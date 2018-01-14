CC=gcc
CFLAGS=-g -Wall
LFLAGS=-c

all: dothi.out

dothi.out: digraph.o
	$(CC) $(CFLAGS) dothi.c digraph.o -o dothi.out -Iinc -Llib -lfdr

digraph.o:
	$(CC) $(CFLAGS) $(LFLAGS) digraph.c -o digraph.o -Iinc -Llib -lfdr

clean:
	rm -rf digraph.o dothi.out 
