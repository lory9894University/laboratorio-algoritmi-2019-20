#ifndef ESERCIZIO1_SORTING_H
#define ESERCIZIO1_SORTING_H

#include <stdio.h>

typedef int (*cmpFunction)(void *, void *);

void quick_sort(void **, int, cmpFunction);

void insertion_sort(void **, size_t, cmpFunction);

#endif //ESERCIZIO1_SORTING_H