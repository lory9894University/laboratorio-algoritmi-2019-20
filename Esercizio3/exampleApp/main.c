#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

typedef struct _pair{
  int key;
  int value;
  int occupied;
}Pair;

/**reads from the file having path "filename" according to the csv format
 * saves the data in a RecordCollection struct (struct containig an array of records and its size)**/
Pair *csv_reading_to_array(char *filename) {
  FILE *fPtr;
  Pair *recordArray;
  char textLine[1024];
  int i = 0;
  char *token;

  recordArray = malloc(sizeof(Pair) * 6321078);
  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }
  while(fgets(textLine,1024,fPtr)!= NULL) {
    token=strtok(textLine,",");
    recordArray[i].key = atoi(token);
    token = strtok(NULL, ",");
    recordArray[i].value = atoi(token);
    i++;
  }

  fclose(fPtr);

  return recordArray;
}

int *random_picker() {
  char *stringSeed = "http://www.youtube.com/watch?v=dQw4w9WgXcQ";
  int numericSeed = 0;
  int i = 0;
  int *keys = malloc(sizeof(int) * 10000000);

  for (i = 0; i < strlen(stringSeed); ++i) {
    numericSeed += (int) stringSeed[i];
  }
  srand(numericSeed);
  for (i = 0; i < 10000000; ++i) {
    keys[i] = rand();
  }
  return keys;
}

void mine_counting_sort(Pair arr[], int range) {
  Pair hostArray[6321078];
  int i;
  Pair count[range + 1];
  for (i = 0; i < range + 1; ++i) {
    count[i].occupied = 0;
  }
  for (i = 0; i < 6321078; ++i) {
    count[arr[i].key].key = arr[i].key;
    count[arr[i].key].value = arr[i].value;
    count[arr[i].key].occupied = 1;
  }
  for (int j = i = 0; i < range + 1; ++i) {
    if (count[i].occupied) {
      arr[j].key = count[i].key;
      arr[j].value = count[i].value;
    }
  }
}

int int_hasher(int *key) {
  return *key;
}

int int_comparer(int a, int b) {
  return a - b;
}

/**this function needs the number of record in the inout file
 * it's a peculiar request but reduces drastically the execution time**/
HashmapPtr csv_reading_to_hashmap(char *filename, int recordnum) {
  FILE *fPtr;
  char textLine[1024];
  int i = 0;
  char *token;
  int *key, *value;
  HashmapPtr hashmap = new_map(recordnum, (void *) int_hasher, (void *) int_comparer);

  key = malloc(sizeof(int) * recordnum);
  value = malloc(sizeof(int) * recordnum);
  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }
  while (fgets(textLine, 1024, fPtr) != NULL) {
    token = strtok(textLine, ",");
    key[i] = atoi(token);
    token = strtok(NULL, ",");
    value[i] = atoi(token);
    insert_entry(hashmap, &key[i], &value[i]);
    i++;
  }

  fclose(fPtr);
}

int file_lines(char *filename) {
  FILE *fPtr;
  int i = 0;
  char *trash;
  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }
  while (fgets(trash, 1024, fPtr) != NULL) {
    i++;
  }

  fclose(fPtr);

  return i;
}

int main(int argc, char **argv) {
  HashmapPtr map;
  Pair *recordArray;
  int *keys;
  int recordNumber;
  if (argc != 3 && argc != 2)
    printf("helper todo..\n");
  if (argc == 3)
    recordNumber = atoi(argv[2]);
  else
    recordNumber = file_lines(argv[1]);

  map = csv_reading_to_hashmap(argv[1], recordNumber);
  recordArray = csv_reading_to_array(argv[1]);
  keys = random_picker();
}