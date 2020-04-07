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

} Hashmap;

/**
 * function gets a key and hashes that value to get the position in the vetor**/
int hashFunction(void* key,Hashmap map){
   int hash=0;

   hash= map.integerCalculator(key)%map.size;

  return hash;
 }

Hashmap * new_map(int size,keyToHash intCalculator){
  Hashmap *map = malloc(sizeof(Hashmap));

  map->entryNum=0;
  map->size = size;
  map->map=(Link)malloc(sizeof(Entry)*size*2);
  map->integerCalculator=intCalculator;

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
    p=&map->map[i];
    while(p->next!=NULL)
      p=p->next;
    while (p->previous!=NULL){
      p=p->previous;
      free(p->next);
    }
    free(p);
  }
  map->entryNum=0;
}

int count_entry(Hashmap * map){
  return map->entryNum;
}

void insert_entry(HashmapPtr map,void* key, void* value,cmpFunction compare){

}

void get_value(HashmapPtr map, void* key,cmpFunction compare){

}
void delete_value(HashmapPtr map, void* key,cmpFunction compare){

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