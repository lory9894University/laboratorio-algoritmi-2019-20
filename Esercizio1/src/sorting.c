#include "sorting.h"
#include <stdio.h>


/*quicksort */
/** partition function takes the element on the right and uses it as a pivot
 * then places the element lower then the pivot on its left and the greather on the right**/
int partition(void **array, int l, int r, cmpFunction comparer) {
  void *pivot = array[r];
  void *tmp;

  for (int i = l; i < r; i++) {
    if (comparer(array[i], pivot) <= 0) {
      tmp = array[l];
      array[l] = array[i];
      array[i] = tmp;
      l++;
    }
  }
  tmp = array[l];
  array[l] = array[r];
  array[r] = tmp;
  return l;
}

/**recursive part of the quick sort algorithm.
 * splits the array according to the pivot and reiterate on the two array**/
void quick_sort_rec(void **array, int l, int r, cmpFunction comparer) {
  int x;

  if (r <= l)
    return;
  x = partition(array, l, r, comparer);
  quick_sort_rec(array, l, x - 1, comparer);
  quick_sort_rec(array, x + 1, r, comparer);

}

/**wrapper of quick sort function**/
void quick_sort(void **array, size_t size, cmpFunction comparer) {
  quick_sort_rec(array, 0, size - 1, comparer);
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


