#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <lcthw/tstree.h>

/*
That means I need to break down `TSTree_insert_base` so that you
understand the insert operation:

...

The key to this data structure is the fact that I'm only
incrementing the character when a `splitchar` is equal. For the other
two conditions, I just walk through the tree until I hit an equal
character to recurse into next. What this does is make it very fast
not to find a key. I can get a bad key, and simply walk through a
few `high` and `low` nodes until I hit a dead end before I know that
this key doesn't exist. I don't need to process every character of
the key or every node of the tree.
*/
static inline TSTree *TSTree_insert_base(
    TSTree *root,
    TSTree *node,
    const char *key,
    size_t len,
    void *value
)
{

    /*
    As I mentioned, if given a `NULL`, then I need to make this node
    and assign the `*key` (current character) to it. This is used to
    build the tree as we insert keys.
    */
    if (node == NULL) {
        node = (TSTree *) calloc(1, sizeof(TSTree));

        if (root == NULL) {
            root = node;
        }

        node->splitchar = *key;
    }

    /*
    If the `*key` is less than this, then recurse, but go to the
    `low` branch.
    */
    if (*key < node->splitchar) {
        node->low = TSTree_insert_base(
            root, node->low, key, len, value
        );
    }

    /*
    This `splitchar` is equal, so I want to go and deal with
    equality. This will happen if we just create this node, so we'll
    be building the tree at this point.
    */
    else if (*key == node->splitchar) {
        /*
        There are still characters to handle, so recurse down the
        `equal` branch, but go to the next `*key` character.
        */
        if (len > 1) {
            node->equal = TSTree_insert_base(
                root, node->equal, key + 1, len - 1, value
            );
        }

        /*
        This is the last character, so I set the value and that's it.
        I have an `assert` here in case of a duplicate.
        */
        else {
            assert(
                node->value == NULL && "Duplicate insert into tst."
            );
            node->value = value;
        }
    }

    /*
    The last condition is that this `*key` is greater than
    `splitchar`, so I need to recurse down the `high` branch.
    */
    else {
        node->high = TSTree_insert_base(
            root, node->high, key, len, value
        );
    }

    return node;
}

/*
For `TSTree_insert`, I'm using the same pattern for recursive
structures where I have a small function that calls the real
recursive function. I'm not doing any additional checks here, but
you should add the usual defensive programming checks to it. One
thing to keep in mind is that it's using a slightly different design
that doesn't have a separate `TSTree_create` function. However, if
you pass it a `NULL` for the `node`, then it will create it and
return the final value.
*/
TSTree *TSTree_insert(
    TSTree *node, const char *key, size_t len, void *value
)
{
    return TSTree_insert_base(node, node, key, len, value);
}

/*
Once you understand that, then move on to analyzing how
`TSTree_search` works.

...

This isn't too difficult to understand, and you can then see that
it's almost exacty the same algorithm for the `TSTree_search_prefix`
function. The only difference is that I'm not trying to find an
exact match, but find the longest prefix I can. To do that, I keep
track of the `last` node that was equal, and then after the search
loop, walk through that node until I find a `value`.
*/
void *TSTree_search(TSTree *root, const char *key, size_t len)
{

    /*
    I don't need to process the tree recursively in the `TSTree`.
    I can just use a `while-loop` and a `node` for where I currently
    am.
    */
    TSTree *node = root;
    size_t i = 0;

    while (i < len && node) {
        /*
        If the current character is less than the node `splitchar`,
        then go low.
        */
        if (key[i] < node->splitchar) {
            node = node->low;
        }

        /*
        If it's equal, then increment `i` and go equal as long as
        it's not the last character. That's why the `if (i < len)`
        is there, so that I don't go too far past the final `value`.
        */
        else if (key[i] == node->splitchar) {
            i++;
            if (i < len)
                node = node->equal;
        }

        /*
        Otherwise, I go `high`, since the character is greater.
        */
        else {
            node = node->high;
        }
    }

    /*
    If I have a node after the loop, then returns its `value`,
    otherwise return `NULL`.
    */
    if (node) {
        return node->value;
    } else {
        return NULL;
    }
}

/*
Looking at `TSTree_search_prefix`, you can start to see the second
advantage a `TSTree` has over the `BSTree` and `Hashmap` for finding
strings. Given any key of X length, you can find any key in X moves.
You can also find the first prefix in X moves, plus N more depending
on how big the matching key is. If the biggest key in the tree is
ten characters long, then you can find any prefix in that key in ten
moves. More importantly, you can do all of this by comparing each
character of the key once.

In comparison, to do the same with a `BSTree`, you would have to
check the prefixes of each character in every possible matching node
in the `BSTree` against the characters in the prefix. It's the same
for finding keys or seeing if a key doesn't exist. You have to
compare each character against most of the characters in the
`BSTree` to find or not find a match.

A `Hashmap` is even worse for finding prefixes, because you can't
hash just the prefix. Basically, you can't do this efficiently in a
`Hashmap` unless the data is something you can parse like a URL.
Even then, that usually requires whole trees of `Hashmap`s.
*/
void *TSTree_search_prefix(TSTree *root, const char *key, size_t len)
{
    if (len == 0)
        return NULL;

    TSTree *node = root;
    TSTree *last = NULL;
    size_t i = 0;

    while (i < len && node) {
        if (key[i] < node->splitchar) {
            node = node->low;
        } else if (key[i] == node->splitchar) {
            i++;
            if (i < len) {
                if (node->value)
                    last = node;
                node = node->equal;
            }
        } else {
            node = node->high;
        }
    }

    node = node ? node : last;

    // traverse until we find the first value in the equal chain
    // this is then the first node with this prefix
    while (node && !node->value) {
        node = node->equal;
    }

    return node ? node->value : NULL;
}

/*
The last two functions should be easy for you to analyze since
they're the typical traversing and destroying operations that
you've already seen in other data structures.
*/

void TSTree_traverse(TSTree *node, TSTree_traverse_cb cb, void *data)
{
    if (!node)
        return;

    if (node->low)
        TSTree_traverse(node->low, cb, data);

    if (node->equal)
        TSTree_traverse(node->equal, cb, data);

    if (node->high)
        TSTree_traverse(node->high, cb, data);

    if (node->value)
        cb(node->value, data);
}

void TSTree_destroy(TSTree *node)
{
    if (node == NULL)
        return;

    if (node->low)
        TSTree_destroy(node->low);

    if (node->equal)
        TSTree_destroy(node->equal);

    if (node->high)
        TSTree_destroy(node->high);

    free(node);
}
