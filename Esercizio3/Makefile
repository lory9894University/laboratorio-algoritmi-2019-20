CFLAGS_Test = -std=c11 -g -I include/ -I ../Resources/C/Unity/
CFLAGS = -std=c11 -g -I include/

all: bin/test bin/exampleApp

test: bin/test

executable: bin/exampleApp

run_test: bin/test
	./bin/test

run_executable: bin/exampleApp
	./bin/exampleApp $(ARGS)

clean:
	$(RM) bin/*
	$(RM) build/*

build/hashmap.o: include/hashmap.h src/hashmap.c 
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/test: include/hashmap.h build/hashmap.o test/test_hashmap.c 
	$(CC) $(CFLAGS_Test) test/test_hashmap.c build/hashmap.o ../Resources/C/Unity/unity.c -o bin/test

bin/exampleApp: include/hashmap.h build/hashmap.o exampleApp/main.c
	$(CC) $(CFLAGS) exampleApp/main.c build/hashmap.o -o bin/exampleApp
