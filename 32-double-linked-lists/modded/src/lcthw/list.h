#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

/*
The first thing I do is create two structures for the `ListNode`
and the `List` that will contain those nodes. This creates the data
structure, which I'll use in the functions and macros that I define
after that. If you read these functions, you'll see that they're
rather simple. I'll be explaining them when I cover the
implementation, but hopefully you can guess what they do.
*/

struct ListNode;

/*
Each `ListNode` has three components within the data structure:

- A value, which is a pointer to anything, and stores the thing we
want to put in the list.
- A `ListNode *next` pointer, which points at another ListNode that
holds the next element in the list.
- A `ListNode *prev` that holds the previous element. Complex,
right? Calling the previous thing "previous." I could have used
"anterior" and "posterior," but only a jerk would do that.
*/
typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

/*
The `List` struct is then nothing more than a container for these
`ListNode` structs that have been linked together in a chain. It
keeps track of the `count`, `first`, and `last` elements of the list.
*/
typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

/*
Returns the number of elements in the list, which is maintained as
elements are added and removed.
*/
#define List_count(A) ((A)->count)

/*
Returns the first element of the list, but doesn't remove it.
*/
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

/*
Finally, take a look at `src/lcthw/list.h:37` where I define the
`LIST_FOREACH` macro. This is a common programming idiom where you
make a macro that generates iteration code so people can't mess it
up. Getting this kind of processing right can be difficult with
data structures, so writing macros helps people out. You'll see
how I use this when I talk about the implementation.

Iterates over the elements in the list.
*/
/*
My own notes for the `LIST_FOREACH()` function macro:
- `L`: pointer to the `List` struct
- `S`: pointer to the first `ListNode` struct part of the list `L`
- `M`: pointer to the next `ListNode` struct that may or may not
(i.e. pointing to `NULL`) be part of the list `L`
- `V`: pointer to the current `ListNode` struct part of the list `L`
*/
#define LIST_FOREACH(L, S, M, V) \
            ListNode *_node = NULL; \
            ListNode *V = NULL; \
            for ( \
                V = _node = L->S; \
                _node != NULL; \
                V = _node = _node->M \
            )

#endif
