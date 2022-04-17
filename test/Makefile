CC = g++
CFLAGS ?= -std=c++17 -pthread
INCLUDE ?= -I../src -I./third_party/goodletest/googletest/include
LIBS ?= ../norodb.a third_party/googletest/lib/libgtest.a
LINK ?= -L..

all: test_byte_buffer
	@echo "\n>>>> ALL DONE! <<<<\n"

test_byte_buffer:
	@echo "\n>>>> TESTING BYTE BUFFER <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_byte_buffer.cc
	@$(CC) $(CFLAGS) -o test_byte_buffer test_byte_buffer.o $(LINK) $(LIBS)
	@./test_byte_buffer
