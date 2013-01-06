#ifndef _darray_algos_h
#define _darray_algos_h

#include <lcthw/darray.h>

typedef int (*DArray_compare)(const void *a, const void *b);
int DArray_qsort(DArray *array, DArray_compare cmp);
//int DArray_heapsort(DArray *array, DArray_compare cmp);
//int DArray_mergesort(DArray *array, DArray_compare cmp);

#endif
