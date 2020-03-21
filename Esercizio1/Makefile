CFLAGS_Test = -std=c11 -I include/ -I ../Resources/C/Unity/
CFLAGS = -std=c11 -I include/

all: bin/test bin/sortingProgram

test: bin/test

executable: bin/sortingProgram

run_test: bin/test
	./bin/test

run_executable: bin/sortingProgram
	./bin/sortingProgram $(ARGS)

clean:
	$(RM) bin/*
	$(RM) build/*

build/sorting.o: include/sorting.h src/sorting.c 
	$(CC) $(CFLAGS) -c src/sorting.c -o build/sorting.o

bin/test: include/sorting.h build/sorting.o test/sorting_test.c 
	$(CC) $(CFLAGS_Test) test/sorting_test.c build/sorting.o ../Resources/C/Unity/unity.c -o bin/test

bin/sortingProgram: include/sorting.h build/sorting.o sortingProgram/main.c
	$(CC) $(CFLAGS) sortingProgram/main.c build/sorting.o -o bin/sortingProgram