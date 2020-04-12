#include "unity.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

int hasher(int *key) {
  return *key;
}

int comparer(int a, int b) {
  return a - b;
}

void empty_map() {
  HashmapPtr map = new_map(0, (keyToHash) hasher, (cmpFunction) comparer);

  TEST_ASSERT_EQUAL(1, is_empty_map(map));

  free_map(map);
}

void deletion() {
  HashmapPtr map = new_map(1, (keyToHash) hasher,
                           (cmpFunction) comparer); //set size to 1, so whatever the hashing function is there is going to be be a list of 3 elements
  int keys[] = {0, 1, 2};
  char values[] = {'a', 'b', 'c'};

  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);
  insert_entry(map, (void *) &keys[2], (void *) &values[2]);

  /**remove the first element of the list**/
  /**this case works even if there are no collisions**/
  TEST_ASSERT_EQUAL(3, count_entry(map));
  TEST_ASSERT_EQUAL(1, delete_entry(map, &keys[0]));
  TEST_ASSERT_EQUAL(2, count_entry(map));

  /**remove the middle element of the list**/
  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  TEST_ASSERT_EQUAL(1, delete_entry(map, &keys[2]));
  TEST_ASSERT_EQUAL(2, count_entry(map));

  /**remove the last element of the list**/
  TEST_ASSERT_EQUAL(1, delete_entry(map, &keys[0]));
  TEST_ASSERT_EQUAL(1, count_entry(map));

  free_map(map);

}

void collision() {
  HashmapPtr map = new_map(2, (keyToHash) hasher, (cmpFunction) comparer);
  int keys[] = {0, 1, 2};
  char values[] = {'a', 'b', 'c'};

  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);
  insert_entry(map, (void *) &keys[2], (void *) &values[2]);

  TEST_ASSERT_EQUAL(3, count_entry(map));

  TEST_ASSERT_EQUAL(values[0], *(char *) get_value(map, &keys[0]));
  TEST_ASSERT_EQUAL(values[1], *(char *) get_value(map, &keys[1]));
  TEST_ASSERT_EQUAL(values[2], *(char *) get_value(map, &keys[2]));

  free_map(map);

}

void clean_restart() {
  HashmapPtr map = new_map(3, (keyToHash) hasher, (cmpFunction) comparer);
  int keys[] = {0, 1, 2};
  char values[] = {'a', 'b', 'c'};

  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);
  insert_entry(map, (void *) &keys[2], (void *) &values[2]);

  TEST_ASSERT_EQUAL(3, count_entry(map));
  cancel_map(map);
  TEST_ASSERT_EQUAL(0, count_entry(map));

  insert_entry(map, (void *) &keys[2], (void *) &values[2]);
  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);

  TEST_ASSERT_EQUAL(3, count_entry(map));

  TEST_ASSERT_EQUAL(values[0], *(char *) get_value(map, &keys[0]));
  TEST_ASSERT_EQUAL(values[1], *(char *) get_value(map, &keys[1]));
  TEST_ASSERT_EQUAL(values[2], *(char *) get_value(map, &keys[2]));

  free_map(map);
}

void only_keys(){
  HashmapPtr map = new_map(2, (keyToHash) hasher, (cmpFunction) comparer);
  int keys[] = {0, 1, 2};
  int *returnedKeys=malloc(sizeof(int)*3);
  char values[] = {'a', 'b', 'c'};

  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);

  TEST_ASSERT_EQUAL(1, verify_key(map,&keys[0]));
  TEST_ASSERT_EQUAL(1, verify_key(map,&keys[1]));
  TEST_ASSERT_EQUAL(0, verify_key(map,&keys[2]));

  free_map(map);
}

void duplicate_keys(){
  HashmapPtr map = new_map(2, (keyToHash) hasher, (cmpFunction) comparer);
  int keys[] = {0, 1, 2};
  char values[] = {'a', 'b', 'c'};

  insert_entry(map, (void *) &keys[0], (void *) &values[0]);
  insert_entry(map, (void *) &keys[1], (void *) &values[1]);
  insert_entry(map, (void *) &keys[1], (void *) &values[2]);


  TEST_ASSERT_EQUAL(2, count_entry(map));

  free_map(map);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(clean_restart);
  RUN_TEST(only_keys);
  RUN_TEST(empty_map);
  RUN_TEST(collision);
  RUN_TEST(deletion);
  RUN_TEST(duplicate_keys);

  UNITY_END();
}