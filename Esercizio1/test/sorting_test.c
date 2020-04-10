#include "unity.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

int numberList[5]={1,5,3,2,7};

static int int_comparer(int *a, int *b) {
  return *a-*b;
}

void empty_array(){
  int ** empty;
  insertion_sort((void*)empty,0,(cmpFunction)int_comparer);
  TEST_PASS();
  quick_sort((void*)empty,0,(cmpFunction)int_comparer);
  TEST_PASS();
}

void casual_array(){
  int ** array;

  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }
  
  insertion_sort((void*)array,5,(cmpFunction)int_comparer);
  TEST_ASSERT_EQUAL(1,*array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);

  array=malloc(sizeof(int *)*5);
    for (int i = 0; i < 5; ++i){
      array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }
  
  quick_sort((void*)array,5,(cmpFunction)int_comparer);
  TEST_ASSERT_EQUAL(1,*array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);
}

void equal_array(){
  int ** array;
  int numberList[5]={1,1,1,1,1};

  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }

  insertion_sort((void*)array,5,(cmpFunction)int_comparer);
  for (int i = 0; i < 5; ++i)
    {
      TEST_ASSERT_EQUAL(1,*array[i]);
    }  

  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }

  quick_sort((void*)array,5,(cmpFunction)int_comparer);
  for (int i = 0; i < 5; ++i)
    {
      TEST_ASSERT_EQUAL(1,*array[i]);
    }
}

void ordered_array(){
  int ** array;
  int orderedList[5]={1,2,3,5,7};


  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&orderedList[i];
  }
  
  insertion_sort((void*)array,5,(cmpFunction)int_comparer);
  TEST_ASSERT_EQUAL(1,*array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);

  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }
  
  quick_sort((void*)array,5,(cmpFunction)int_comparer);
  TEST_ASSERT_EQUAL(1,*array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);
}


void inverted_array(){
  int **array;
  int numberList[5] = {7, 5, 3, 2, 1};


  array = malloc(sizeof(int *) * 5);
  for (int i = 0; i < 5; ++i) {
    array[i] = malloc(sizeof(int));
    array[i] = &numberList[i];
  }

  insertion_sort((void *) array, 5, (cmpFunction) int_comparer);
  TEST_ASSERT_EQUAL(1, *array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);

  array=malloc(sizeof(int *)*5);
  for (int i = 0; i < 5; ++i){
    array[i]=malloc(sizeof(int));
    array[i]=&numberList[i];
  }
  
  quick_sort((void*)array,5,(cmpFunction)int_comparer);
  TEST_ASSERT_EQUAL(1,*array[0]);
  TEST_ASSERT_EQUAL(2,*array[1]);
  TEST_ASSERT_EQUAL(3,*array[2]);
  TEST_ASSERT_EQUAL(5,*array[3]);
  TEST_ASSERT_EQUAL(7,*array[4]);

}

int main(){
  UNITY_BEGIN();

  RUN_TEST(empty_array);
  RUN_TEST(casual_array);
  RUN_TEST(equal_array);
  RUN_TEST(ordered_array);
  RUN_TEST(inverted_array);

  UNITY_END();
}
