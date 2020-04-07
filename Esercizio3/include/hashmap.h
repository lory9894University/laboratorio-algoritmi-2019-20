
#ifndef ESERCIZIO3_HASHMAP_H
#define ESERCIZIO3_HASHMAP_H

typedef struct _hashmap * HashmapPtr;
typedef int (* cmpFunction) (void *, void *);
typedef int (* keyToHash) (void *);

HashmapPtr new_map(int size,keyToHash intCalculator);
void free_map(HashmapPtr  map);
int is_empty_map(HashmapPtr map);
void cancel_map(HashmapPtr map);
int count_entry(HashmapPtr map);
void insert_entry(HashmapPtr map,void* key, void* value,cmpFunction compare);
void get_value(HashmapPtr map, void* key,cmpFunction compare);
void delete_value(HashmapPtr map, void* key,cmpFunction compare);
void ** get_keys(HashmapPtr map);
#endif //ESERCIZIO3_HASHMAP_H
