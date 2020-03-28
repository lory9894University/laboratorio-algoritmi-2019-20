#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct _pair{
  int key;
  int value;
  int occupied;
}Pair;

void mineCountingSort(Pair arr[], int range){
  Pair hostArray[6321078];
  int i;
  Pair count[range + 1];
  for (i = 0; i <range +1 ; ++i) {
    count[i].occupied=0;
  }
  for (i = 0; i <6321078 ; ++i) {
    count[arr[i].key].key=arr[i].key;
    count[arr[i].key].value=arr[i].value;
    count[arr[i].key].occupied=1;
  }
  for (int j=i=0; i <range +1 ; ++i) {
    if (count[i].occupied){
      arr[j].key=count[i].key;
      arr[j].value=count[i].value;
    }
  }
}
int main(){

}