CC = g++
CFLAGS ?= -std=c++11
INCLUDE ?= -I../src
LIB_NORODB ?= ../norodb.a
LINK ?= -L.. 

all:
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cc 
	$(CC) -o main main.o $(LINK) $(LIB_NORODB) 
	./main
