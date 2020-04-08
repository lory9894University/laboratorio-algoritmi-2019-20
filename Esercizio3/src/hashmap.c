#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _entry * Link;
typedef struct _entry{
  void * key;
  void * value;
  Link next,previous;
} Entry;

typedef struct _hashmap{
  Entry * map;
  int entryNum,size;
  keyToHash integerCalculator;
  cmpFunction comparer;

} Hashmap;

/**function gets a key and hashes that value to get the position in the vetor**/
int hashFunction(void* key,Hashmap map){
   int hash=0;

   hash= map.integerCalculator(key)%map.size;

  return hash;
 }

Hashmap *new_map(int size, keyToHash intCalculator, cmpFunction comparer) {
  Hashmap *map = malloc(sizeof(Hashmap));

  map->entryNum = 0;
  map->size = size;
  map->map = (Link) malloc(sizeof(Entry) * size);
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
  Link p;
  //TODO: devo deallocare i puntatori a void delle entry?
  for (int i = 0; i <map->size ; ++i) {
    p = &map->map[i];
    while (p->next != NULL)
      p = p->next;
    while (p->previous != NULL) {
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
  Link p;

  p = &map->map[index];
  while (p->next != NULL) {
    if (map->comparer(p->key, key) == 0) {
      return 1;
    }
    p = p->next;
  }
  return 0;
}

int count_entry(Hashmap *map) {
  return map->entryNum;
}

void insert_entry(HashmapPtr map, void *key, void *value) {
  int index = hashFunction(key, *map);
  Link p;

  if (map->map[index].key == NULL) {
    map->map[index].key = key;
    map->map[index].value = value;
    map->entryNum++;
  } else {
    p = &map->map[index];
    while (p->next != NULL) {
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
    map->entryNum++;
  }
}

void *get_value(HashmapPtr map, void *key) {
  int index = hashFunction(key, *map);
  Link p;

  p = &map->map[index];
  while (p->next != NULL) {
    if (map->comparer(p->key, key) == 0) {
      break;
    }
    p = p->next;
  }
  if (p->key != NULL && map->comparer(p->key, key) == 0)
    return p->value;
  else {
    //printf("element not found\n");
    return NULL;
  }

}

int delete_entry(HashmapPtr map, void *key) {
  int index = hashFunction(key, *map);
  Link p, head;

  head = p = &map->map[index];
  while (p->next != NULL) {
    if (map->comparer(p->key, key) == 0) {
      break;
    }
    p = p->next;
  }
  if (map->comparer(p->key, key) != 0) {
    printf("element not found\n");
    return 0;
  }
  map->entryNum--; //element found, decrese entry number even if it's not yet deleted
  //TODO: that's a bodge. fix it if you find a better way
  if (p == head && p->next != NULL) {
    map->map[index] = *p->next;
    map->map[index].previous = NULL;
  } else if (p == head) {
    p->key = NULL;
    p->value = NULL;
  } else {
    p->previous->next = p->next;
  }
  free(p);
  return 1;
}

void ** get_keys(HashmapPtr map){
  void **keys;
  int c=0;
  Link p;

  keys=malloc(sizeof(void*)*map->entryNum);
  for (int i = 0; i <map->size ; ++i) {
    if (map->map[i].value!=NULL){
      p=&map->map[i];
      while(p->next!=NULL)
        p=p->next;
      while (p->previous!=NULL){
        p=p->previous;
        keys[c]=p->next;
        c++;
      }
      keys[c]=p;
      c++;
    }
  }

  return keys;
}