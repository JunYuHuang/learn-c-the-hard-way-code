/*
This header file is showing you a new technique where I put
`static inline` functions right in the header. These function
definitions will work similar to the `#define` macros that you've
been making, but they're cleaner and easier to write. If you need
to create a block of code for a macro and you don't need code
generation, then use a `static inline` function.

Compare this technique to the `LIST_FOREACH` that generates a proper
`for-loop` for a list. This would be impossible to do with a
`static inline` function because it actually has to generate the
inner block of code for the loop. The only way to do that is with a
callback function, but that's not as fast and it's harder to use.
*/

#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

/*
`DArray` struct notes:
- stores an array of pointers
- `end`: index of last element in `DArray`
- `max`: max size or count of elements in `DArray`
- `element_size`: size of each element in `DArray`
- `expand_rate`: count of element slots to add to `DArray` should
`DArray` meet or exceed `max` total elements
- `contents`: actual static array or pointer of elements in `DArray`
*/
typedef struct DArray {
    int end;
    int max;
    size_t element_size;
    size_t expand_rate;
    void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void DArray_set(DArray *array, int i, void *el)
{
    check(array != NULL, "Invalid array.");
    check(i < array->max, "darray attempt to set past max");
    if (i > array->end)
        array->end = i;
    array->contents[i] = el;
error:
    return;
}

static inline void *DArray_get(DArray *array, int i)
{
    check(array != NULL, "Invalid array.");
    check(i < array->max, "darray attempt to get past max");
    return array->contents[i];
error:
    return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
    check(array != NULL, "Invalid array.");
    void *el = array->contents[i];

    array->contents[i] = NULL;

    return el;

error:  // fallthrough
    return NULL;
}

/*
- returns a pointer for memory allocated for a 1-sized array given an existing `DArray`
- returns a new element of the element size of a given existing `DArray`
*/
static inline void *DArray_new(DArray *array)
{
    check(array != NULL, "Invalid array.");
    check(
        array->element_size > 0,
        "Can't use DArray_new on 0 size darrays."
    );

    return calloc(1, array->element_size);

error:
    return NULL;
}

#define DArray_free(E) free((E))

#endif
