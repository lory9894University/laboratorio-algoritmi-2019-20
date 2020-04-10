#include "sorting.h"
#include <stdio.h>


/*quicksort */
/** partition function takes the element on the right and uses it as a pivot
 * then places the element lower then the pivot on its left and the greather on the right**/
int partition(void **arr, int low, int high, cmpFunction comparer) {
  void *temp;
  void *pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
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
void quick_sort(void **array, int size, cmpFunction comparer) {
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


