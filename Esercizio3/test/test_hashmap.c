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

void empty_map(){
  HashmapPtr map=new_map(0,(keyToHash) hasher,(cmpFunction)comparer);

  TEST_ASSERT_EQUAL(1,is_empty_map(map));

  free_map(map);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(empty_map);

  UNITY_END();
}