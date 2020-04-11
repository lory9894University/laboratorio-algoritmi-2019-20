#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**this structure can be used as an element of the structure HashMap or as a node in a list (for the same structure)**/
typedef struct _entry * Link;
typedef struct _entry{
  void * key;
  void * value;
  int sentinel;
  Link next,previous;
} Entry;

/**hash map structure, saves every information needed during construction, so there's no need to 
write them every time the function are used**/
typedef struct _hashmap{
  Entry * map;
  int entryNum,size;
  double A;
  keyToHash integerCalculator;
  cmpFunction comparer;
} Hashmap;

/**function gets a key and hashes that value to get the position in the vector**/
int hashFunction(void* key,Hashmap map){
   int hash=0;
   int k= map.integerCalculator(key);
   hash=(((k*map.A)-(int)(k*map.A))*map.size);

  return hash;
 }

Hashmap *new_map(int size, keyToHash intCalculator, cmpFunction comparer) {
  Hashmap *map = malloc(sizeof(Hashmap));

  map->entryNum = 0;
  map->size = size;
  map->A=(sqrt(5)-1)/2;
  map->map = (Link) malloc(sizeof(Entry) * size);
  for (int i = 0; i <map->size ; ++i) {
    map->map[i].sentinel=1;
    map->map[i].previous=map->map[i].next=&map->map[i];
  }
  map->integerCalculator = intCalculator;
  map->comparer = comparer;

  return map;
}

void free_map(Hashmap * map){
  cancel_map(map);
  free(map->map);
  free(map);
}

int is_empty_map(Hashmap * map){
  return map->entryNum==0;
}

void cancel_map(Hashmap * map){
  Link p,sentinel;
  for (int i = 0; i <map->size ; ++i) {
    sentinel = p = &map->map[i];
    while (p->previous != sentinel) {
      p = p->previous;
      free(p->next);
    }
    p->value = NULL;
    p->key = NULL;
  }
  map->entryNum = 0;
}

int verify_key(HashmapPtr map, void *key) {
  int index = hashFunction(key, *map);
  Link p,sentinel;

  sentinel= p = &map->map[index];
  while (p->next !=sentinel ) {
    if (map->comparer(p->key, key) == 0) {
      return 1;
    }
    p = p->next;
  }
  if (map->comparer(p->key, key) == 0) 
      return 1;
  return 0;
}

int count_entry(Hashmap *map) {
  return map->entryNum;
}

void insert_entry(HashmapPtr map, void *key, void *value) {
  int index = hashFunction(key, *map);
  Link p,sentinel;

  /*The insertion should be made as the head of the list but
   * sacrificing a bit of time on insertion i can check for duplicate keys*/
  p = sentinel = &map->map[index];
    while (p->next != sentinel) {
      if (map->comparer(p->key, key) == 0) {
        printf("found duplicate key, skipping\n");
        return;
      }
      p = p->next;
    }
    if (map->comparer(p->key, key) == 0) {
      printf("found duplicate key, skipping\n");
      return;
    }
  p->next = malloc(sizeof(*p));
  p->next->previous = p;
  p = p->next;
  p->value = value;
  p->key = key;
  p->next=sentinel;
  map->entryNum++;

}

void *get_value(HashmapPtr map, void *key) {
  int index = hashFunction(key, *map);
  Link p,sentinel;

  sentinel = p = &map->map[index];
  while (p->next != sentinel && (map->comparer(p->key, key) == 0)) {
    p = p->next;
  }
  if (p->key != sentinel && map->comparer(p->key, key) == 0)
    return p->value;
  else {
    printf("element not found\n");
    return NULL;
  }

}

int delete_entry(HashmapPtr map, void *key) {
  int index = hashFunction(key, *map);
  Link p, sentinel;

  sentinel = p = &map->map[index];
  while (p->next != sentinel && (map->comparer(p->key, key) == 0)) {
    p = p->next;
  }
  if (map->comparer(p->key, key) != 0) {
    printf("element not found\n");
    return 0;
  }
  map->entryNum--; //element found, decrese entry number even if it's not yet deleted
  p->previous->next=p->next;
  p->next->previous=p->previous;
  free(p);
  return 1;
}

void ** get_keys(HashmapPtr map){
  void **keys;
  int c=0;
  Link p,sentinel;

  keys=malloc(sizeof(void*)*map->entryNum);
  for (int i = 0; i <map->size ; ++i) {
    p=sentinel=&map->map[i];
    while (p->previous!=sentinel){
      p=p->previous;
      keys[c]=p;
      c++;
    }
  }

  return keys;
}