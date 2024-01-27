CC = g++
CFLAGS ?= -std=c++20
INCLUDE ?= -I../src
LIB_NORODB ?= ../norodb.a
LINK ?= -L.. 

all: 
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cc 
	$(CC) $(CFLAGS) -o main main.o $(LINK) $(LIB_NORODB) 
	./main


loop: clean
	$(CC) $(CFLAGS) $(INCLUDE) -c loop.cc
	$(CC) $(CFLAGS) -o loop loop.o $(LINK) $(LIB_NORODB) 
	./loop

clean:
	rm -rf norodb || true
	rm -rf *.o || true
