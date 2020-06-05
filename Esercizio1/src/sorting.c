#include "sorting.h"
#include <stdio.h>

/** 3-way partition based quick sort**/
/** This function partitions a[] in three parts
   a) a[l..i] contains all elements smaller than pivot 
   b) a[i+1..j-1] contains all occurrences of pivot 
   c) a[j..r] contains all elements greater than pivot **/
void partition_tri(void ** a, int l, int r, int *i, int *j,cmpFunction compare) {
  *i = l-1, *j = r;
  int p = l-1, q = r;
  void * v = a[r];
  void * temp;
  
  while (1){
    while (compare(a[*i=*i+1],v)<0);

    while (compare(v , a[*j=*j-1])<0) {
      if (*j == l)
      break;
    }
    if (*i >= *j) break;
  
    temp = a[*i];
    a[*i]=a[*j];
    a[*j]=temp;
  
    if (compare(a[*i],v)==0)
    { 
      p++; 
      temp = a[*i];
      a[*i]=a[p];
      a[p]=temp;
    } 
  
    if (compare(a[*j],v)==0)
    { 
      q--; 
      temp = a[*j];
      a[*j]=a[q];
      a[q]=temp;
    } 
  } 
  
  temp = a[*i];
  a[*i]=a[r];
  a[r]=temp;
  
  *j = *i-1;
  for (int k = l; k < p; k++, *j=*j-1) {
    temp = a[*j];
    a[*j]=a[k];
    a[k]=temp;
  }
  
  *i = *i+1;
	for (int k = r-1; k > q; k--, *i=*i+1) {
    temp = a[*i];
    a[*i]=a[k];
    a[k]=temp;
  }
}

/**recursive part of the 3-way quick sort algorithm.
 * splits the array according to the pivot and reiterate on two of the three array
 * It doesn't iterate on the "middle" array, because every element is identycal**/
void quicksort_tri(void **a, int l, int r,cmpFunction compare) {
  if (r <= l) return;

  int i, j;

  partition_tri(a, l, r, &i, &j, compare);
  quicksort_tri(a, l, j, compare);
  quicksort_tri(a, i, r, compare);
}

/** partition function takes the element on the right and uses it as a pivot
 * then places the element lower then the pivot on its left and the greather on the right**/
int partition(void **arr, int low, int high, cmpFunction comparer) {
  void *temp;
  void *pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j--) {
    if (comparer(arr[j], pivot) < 0) {
      i++;
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return (i + 1);
}

/**wrapper of quick sort function**/
void quick_sort(void **array, int size, cmpFunction comparer) {
  quicksort_tri(array,0,size-1,comparer);

}

/*insertion sort*/
/**insertion sort algorithm, no need for a wrapper**/
void insertion_sort(void **array, size_t size, cmpFunction comparer) {
  void *temp;
  int j = 0;

  for (int i = 0; i < size; ++i) {
  temp = array[i];
  for (j = i - 1; j >= 0 && comparer(array[j], temp) > 0; j--) {
    array[j + 1] = array[j];
  }
  array[j + 1] = temp;
  }
}


