/*
That's the whole implementation of the `darray_algos.c` file, and it
should work on most modern UNIX systems. What each of these does is
sort the `contents` store of void pointers using the
`DArray_compare` that you give it.
*/
#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    return heapsort(
        array->contents, DArray_count(array), sizeof(void *), cmp
    );
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    return mergesort(
        array->contents, DArray_count(array), sizeof(void *), cmp
    );
}
