CC=gcc
CFLAGS= -g
OBJS=adjgraph.o

all: metro.out

metro.out: $(OBJS)
	$(CC) $(CFLAGS) metro.c $(OBJS) -o metro.out -I./inc -L./lib -lfdr

adjgraph.o:
	$(CC) $(CFLAGS) -c adjgraph.c -o $(OBJS) -I./inc -L./lib -lfdr

clean:
	rm -rf *.o metro.out testcase3