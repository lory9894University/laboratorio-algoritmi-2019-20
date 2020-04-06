
#ifndef ESERCIZIO3_HASHMAP_H
#define ESERCIZIO3_HASHMAP_H

typedef struct _hashmap * HashmapPtr;

HashmapPtr new_map(int size);
void free_map(HashmapPtr  map);
int is_empty_map(HashmapPtr map);
void cancel_map(HashmapPtr map);
int count_entry(HashmapPtr map);
void insert_entry(HashmapPtr map,void* key, void* value);
void get_value(HashmapPtr map, void* key);
void delete_value(HashmapPtr map, void* key);
void ** get_keys(HashmapPtr map);
#endif //ESERCIZIO3_HASHMAP_H
