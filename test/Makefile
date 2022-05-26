CC = g++
CFLAGS ?= -std=c++17 -pthread
INCLUDE ?= -I../src -I./third_party/goodletest/googletest/include
LIBS ?= ../norodb.a third_party/googletest/lib/libgtest.a
LINK ?= -L..

all: test_byte_buffer test_db_directory
	@echo "\n>>>> ALL DONE! <<<<\n"

test_byte_buffer:
	@echo "\n>>>> TESTING BYTE BUFFER <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_byte_buffer.cc
	@$(CC) $(CFLAGS) -o test_byte_buffer test_byte_buffer.o $(LINK) $(LIBS)
	@./test_byte_buffer


test_db_directory:
	@echo "\n>>>> TESTING DB DIRECTORY <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_db_directory.cc
	@$(CC) $(CFLAGS) -o test_db_directory test_db_directory.o $(LINK) $(LIBS)
	@./test_db_directory

test_row:
	@echo "\n>>>> TESTING ROW <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_row.cc
	@$(CC) $(CFLAGS) -o test_row test_row.o $(LINK) $(LIBS)
	@./test_row

test_index:
	@echo "\n>>>> TESTING INDEX <<<<\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c test_index.cc
	@$(CC) $(CFLAGS) -o test_index test_index.o $(LINK) $(LIBS)
	@./test_index
