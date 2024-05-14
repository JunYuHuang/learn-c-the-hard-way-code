#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

// bubble sort
typedef int (*List_compare) \
    (const void *value_1, const void *value_2);
int List_bubble_sort(List *list, List_compare compare_cb);

// merge sort
// - TODO

#endif
