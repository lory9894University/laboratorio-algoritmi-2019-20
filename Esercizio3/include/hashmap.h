
#ifndef ESERCIZIO3_HASHMAP_H
#define ESERCIZIO3_HASHMAP_H

typedef struct _hashmap * HashmapPtr;

HashmapPtr newMap(int size);
void freeMap(HashmapPtr  map);
int isEmptyMap(HashmapPtr map);
void cancelMap(HashmapPtr map);
int countEntry(HashmapPtr map);
void insertEntry(HashmapPtr map,void* key, void* value);
void getValue(HashmapPtr map, void* key);
void deleteValue(HashmapPtr map, void* key);
void ** getKeys(HashmapPtr map);
#endif //ESERCIZIO3_HASHMAP_H
