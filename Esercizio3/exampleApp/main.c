#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashmap.h"

typedef struct _pair{
  int key;
  int value;
  int occupied;
}Pair;

/**reads from the file having path "filename" according to the csv format
 * saves the data in a RecordCollection struct (struct containig an array of records and its size)**/
Pair *csv_reading_to_array(char *filename, int *range) {
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
    token = strtok(textLine, ",");
    recordArray[i].key = atoi(token);
    token = strtok(NULL, ",");
    recordArray[i].value = atoi(token);
    if (*range < recordArray[i].key)
      *range = recordArray[i].key;
    i++;
  }

  fclose(fPtr);

  return recordArray;
}

/**picks 10000000 random keys from an hardcoded seed (to make multiple run coherent)**/
int *random_picker() {
  int numericSeed = 3959;
  int i = 0;
  int *keys = malloc(sizeof(int) * 10000000);

  srand(numericSeed);
  for (i = 0; i < 10000000; ++i) {
    keys[i] = rand() % 10000000;
  }
  return keys;
}

/*adaptation of counting sort to order the array of records*/
void mine_counting_sort(Pair *arr, int range) {
  int i;
  Pair *count = malloc(sizeof(Pair) * range + 1);
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
      j++;
    }
  }
  free(count);
}

/**this functions needs to be passed to the hash-map library because without knowing the data type
* i cant immagine a way to compare the keys or hash them (more explanation in hashmap.h)**/
int int_hasher(int *key) {
  return *key;
}

int int_comparer(int *a, int *b) {
  return *a - *b;
}

/**this function needs the number of record in the inpout file
 * it's a peculiar request but reduces the execution time**/
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
  return hashmap;
}

/*simply counts the lines in the file*/
int file_lines(char *filename) {
  FILE *fPtr;
  int i = 0;
  char *trash = malloc(sizeof(char) * 1024);
  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }
  while (fgets(trash, 1024, fPtr) != NULL) {
    i++;
  }

  fclose(fPtr);
  free(trash);
  return i;
}

/*get the value stored in the hashmap corresponding to the keys in the array "keys"
* return the number of keys found*/
int hash_get(HashmapPtr map, int *keys, int lenght) {
  int valuesFound = 0;
  for (int i = 0; i < lenght; ++i) {
    if (get_value(map, &keys[i])) {
      valuesFound++;
    }
  }
  return valuesFound;
}


int binary_search(int key, int l, int r, Pair *recordArray) {
  int mid = l + (r - l) / 2;
  if (r < l)
    return 0;
  if (recordArray[mid].key == key)
    return 1;
  if (recordArray[mid].key < key)
    return binary_search(key, mid + 1, r, recordArray);
  else
    return binary_search(key, l, mid - 1, recordArray);
}

/**gets the value saved in the array corresponfign to the elements saved in the keys array**/
int array_get(Pair *recordArray, int *keys, int lenght) {
  int valuesFound = 0;

  for (int i = 0; i < lenght; ++i) {
    if (binary_search(keys[i], 0, 6321078, recordArray))
      valuesFound++;
  }
  return valuesFound;
}

int main(int argc, char **argv) {
  HashmapPtr map;
  Pair *recordArray;
  int *keys;
  int recordNumber, range;
  int last = 0;
  clock_t begin, end;
  double time_spent;


  if (argc != 3 && argc != 2)
    printf("insert the file path as the first argument,
    	the number of lines as the second (optional)\n");
  if (argc == 3)
    recordNumber = atoi(argv[2]);
  else
    recordNumber = file_lines(argv[1]);

  begin = clock();
  map = csv_reading_to_hashmap(argv[1], recordNumber);
  end = clock();
  time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
  printf("time passed for acquisition in hash map: %f\n", time_spent);

  begin = clock();
  recordArray = csv_reading_to_array(argv[1], &range);
  mine_counting_sort(recordArray, range);
  end = clock();
  time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
  printf("time passed for acquisition in array: %f\n", time_spent);

  keys = random_picker();
  begin = clock();
  printf("keys found from hashmap: %d\n", hash_get(map, keys, 10000000));
  end = clock();
  time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
  printf("time needed to get keys from hashmap: %f\n", time_spent);
  begin = clock();
  printf("keys found from array: %d\n", array_get(recordArray, keys, 10000000));
  end = clock();
  time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
  printf("time needed to get key from array: %f\n", time_spent);
  return 0;
}