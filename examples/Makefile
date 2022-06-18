CC = g++
CFLAGS ?= -std=c++17
INCLUDE ?= -I../src
LIB_NORODB ?= ../norodb.a
LINK ?= -L.. 

all: clean
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cc 
	$(CC) $(CFLAGS) -o main main.o $(LINK) $(LIB_NORODB) 
	./main

clean:
	rm -rf norodb || true
