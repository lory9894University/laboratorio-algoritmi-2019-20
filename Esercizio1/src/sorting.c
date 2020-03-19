#include "sorting.h"
#include <stdio.h>

void swap(void *a,void *b){
  void *c = &b;
  b=&a;
  a=&c;
}
/*quicksort */
int partition(void * array, int l,int r){
  return 0;
}

void quick_sort_rec(void * array, int l,int r){
  int x;

  if (r <=l)
    return;
  x= partition(array,l,r);
  quick_sort_rec(array,l,x-1);
  quick_sort_rec(array,x+1,l);

}

void quick_sort(void * array, size_t size,cmpFunction comparer){
  quick_sort_rec(array,0,size);
}

/*insertion sort*/

void insertion_sort(void * array,size_t size,cmpFunction comparer){
  void * temp;
  int j=0;

  for (int i = 0; i <size ; ++i) {
    temp = &array[i];
    for (j= i-1 ; j>=0 && comparer(&array[j],temp)>0; j--){
      swap(&array[j+1],&array[j]);
    }
    swap(&array[j+1],temp);
  }
}


