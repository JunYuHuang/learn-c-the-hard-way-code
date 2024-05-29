/*
The final data structure that I'll show you is called the TSTree,
which is similar to the `BSTree`, except it has three branches:
`low`, `equal`, and `high`. It's primarily used just like `BSTree`
and `Hashmap` to store key/value data, but it works off of the
individual characters in the keys. This gives the `TSTree` some
abilities that neither `BSTree` nor `Hashmap` has.

In a `TSTree`, every key is a string, and it's inserted by walking
through and building a tree based on the equality of the characters
in the string. It starts at the root, looks at the character for
that node, and if it's lower, equal to, or higher than that, then it
goes in that direction. You can see this in the header file:
*/

#ifndef _lcthw_TSTree_h
#define _lcthw_TSTree_h

#include <stdlib.h>
#include <lcthw/darray.h>

/*
The TSTree has the following elements:
- splitchar: The character at this point in the tree.
- low: The branch that's lower than `splitchar`.
- equal: The branch that's equal to `splitchar`.
- high: The branch that's higher than `splitchar`.
- value: The value set for a string at that point with `splitchar`.
*/
typedef struct TSTree {
    char splitchar;
    struct TSTree *low;
    struct TSTree *equal;
    struct TSTree *high;
    void *value;
} TSTree;

/*
A typical operation to find a value for this `key`.
*/
void *TSTree_search(TSTree *root, const char *key, size_t len);

/*
This operation finds the first value that has this as a prefix of its
key. This is the an operation that you can't easily do in a `BSTree`
or `Hashmap`.
*/
void *TSTree_search_prefix(
    TSTree *root, const char *key, size_t len
);

typedef void (*TSTree_traverse_cb) (void *value, void *data);

/*
This breaks the `key` down by each character and inserts them into
the tree.
*/
TSTree *TSTree_insert(
    TSTree *node, const char *key, size_t len, void *value
);

/*
This walks through the tree, allowing you to collect or analyze all
the keys and values it contains.
*/
void TSTree_traverse(
    TSTree *node, TSTree_traverse_cb cb, void *data
);

void TSTree_destroy(TSTree *root);

#endif

/*
The only thing missing is a `TSTree_delete`, and that's because
it's a horribly expensive operation, even more expensive than
`BSTree_delete`. When I use `TSTree` structures, I treat them as
constant data that I plan on traversing many times, and not removing
anything from them. They are very fast for this, but aren't good if
you need to insert and delete things quickly. For that, I use
`Hashmap`, since it beats both `BSTree` and `TSTree`.
*/
