
#ifndef ESERCIZIO3_HASHMAP_H
#define ESERCIZIO3_HASHMAP_H

typedef struct _hashmap *HashmapPtr;

typedef int (*cmpFunction)(void *, void *);

typedef int (*keyToHash)(void *);

/**map constructor
 * needs a size ccording to the disposable memory (more dedicated memory = better execution time)
 * a compare function and a function that transforms the key into an "hashable" integer needs to be passed as parameters
 * more on KeyToHash: a function that, given the key, returns an integer derivated from the key that che be hashed**/
HashmapPtr new_map(int size, keyToHash intCalculator, cmpFunction compare);
/**map distructor**/
void free_map(HashmapPtr map);
/**check if a map is empty, returns 1 for true**/
int is_empty_map(HashmapPtr map);
/**returns the number of entry of a given map**/
int count_entry(HashmapPtr map);
/**deletes every records in the map, not the map**/
void cancel_map(HashmapPtr map);

/** return 1 if a given key is present in the map**/
int verify_key(HashmapPtr map, void *key);

/** insert a new <K,V> entry**/
void insert_entry(HashmapPtr map, void *key, void *value);

/**returns the void pointer the value associated with the given key**/
void *get_value(HashmapPtr map, void *key);

/**delete the entry associated with the given key**/
int delete_entry(HashmapPtr map, void *key);

/**returns a list of the keys saved in the hashmap**/
void **get_keys(HashmapPtr map);

#endif //ESERCIZIO3_HASHMAP_H
