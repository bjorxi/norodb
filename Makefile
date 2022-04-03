CC = g++
CFLAGS = -std=c++17 -lstdc++fs
OBJECTS = 

all: db.o db_directory.o row.o coding.o byte_buffer.o
	ar rcs norodb.a db.o db_directory.o row.o coding.o byte_buffer.o

db_directory.o: 
	$(CC) $(CFLAGS) -c src/db_directory.cc

db.o: 
	$(CC) $(CFLAGS) -c src/db.cc

row.o:
	$(CC) $(CFLAGS) -c src/row.cc

coding.o:
	$(CC) $(CFLAGS) -c src/third_party/leveldb/coding.cc

byte_buffer.o:
	$(CC) $(CFLAGS) -c src/byte_buffer.cc


clean:
	rm *.o || true
	rm *.a || true
