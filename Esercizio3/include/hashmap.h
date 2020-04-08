
#ifndef ESERCIZIO3_HASHMAP_H
#define ESERCIZIO3_HASHMAP_H

typedef struct _hashmap *HashmapPtr;

typedef int (*cmpFunction)(void *, void *);

typedef int (*keyToHash)(void *);

/**map constructor**/
HashmapPtr new_map(int size, keyToHash intCalculator, cmpFunction compare);

/**map distructor**/
void free_map(HashmapPtr map);

/**check if a map is empty, returns 1 for true**/
int is_empty_map(HashmapPtr map);

/**returns the number of entry of a given map**/
int count_entry(HashmapPtr map);

/**deletes every records in the map, not the map**/
void cancel_map(HashmapPtr map);

int verify_key(HashmapPtr map, void *key);

void insert_entry(HashmapPtr map, void *key, void *value);

void *get_value(HashmapPtr map, void *key);

int delete_entry(HashmapPtr map, void *key);

void **get_keys(HashmapPtr map);

#endif //ESERCIZIO3_HASHMAP_H
