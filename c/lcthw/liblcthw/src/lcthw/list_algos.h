#ifndef _lcthw_list_algos_h
#define _lcthw_list_algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(void *a, void *b);

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

#endif
