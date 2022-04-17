CC = g++
CFLAGS ?= -std=c++17 -pthread
INCLUDE ?= -I../src -I./third_party/goodletest/googletest/include
LIBS ?= ../norodb.a third_party/googletest/lib/libgtest.a
LINK ?= -L..


test_byte_buffer:
	$(CC) $(CFLAGS) $(INCLUDE) -c test_byte_buffer.cc
	$(CC) $(CFLAGS) -o test_byte_buffer test_byte_buffer.o $(LINK) $(LIBS)
	./test_byte_buffer
