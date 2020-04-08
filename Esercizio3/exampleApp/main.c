#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

typedef struct _pair{
  int key;
  int value;
  int occupied;
}Pair;

/**reads from the file having path "filname" according to the csv format
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
  }

  fclose(fPtr);

  return recordArray;
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

int main() {

}