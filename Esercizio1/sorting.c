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

void quick_sort(void * array, size_t size){
  quick_sort_rec(array,0,size);
}

/*insertion sort*/

void insertion_sort(void ** array,size_t size, int isDecreasing){
  //todo:ogni algoritmo deve permettere di specificare (cioè deve accettare in input) il
  // criterio secondo cui ordinare i dati. .....non ho capito

  //todo: questo array di puntatori che viene ordinato non mi convince proprio....
  void * temp;
  int j=0;
  for (int i = 0; i <size ; ++i) {
    temp = &array[i];
    for (j= i-1 ; j>=0 && array[j]>temp; j--){
      array[j+1]=&array[j];
    }
    array[j+1]=temp;
  }
}


