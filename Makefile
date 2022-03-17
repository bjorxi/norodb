CC = g++
CFLAGS = -std=c++11
OBJECTS = 

all: db.o 
	ar rcs norodb.a db.o 

db.o: src/db.h src/db_options.h
	$(CC) $(CFLAGS) -c src/db.cc

clean:
	rm *.o || true
	rm *.a || true
