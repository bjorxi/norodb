CC = g++
CFLAGS = -std=c++17 -lstdc++fs
OBJECTS =

build: db.o db_directory.o row.o coding.o byte_buffer.o db_file.o index.o
	ar rcs norodb.a db.o db_directory.o row.o coding.o byte_buffer.o db_file.o index.o

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

db_file.o:
	$(CC) $(CFLAGS) -c src/db_file.cc

index.o:
	$(CC)  $(CFLAGS) -c  src/index.cc


test: build
	@echo "\n\n >>>> RUNNING TESTS <<<<\n\n"
	make -B -C test/


format:
	find . -iname '*.h' -o -iname '*.cc' | xargs clang-format -i

clean:
	rm *.o || true
	rm *.a || true
