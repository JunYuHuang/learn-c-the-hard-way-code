#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring) a, (bstring) b);
}

BSTree *BSTree_create(BSTree_compare compare)
{
    BSTree *map = calloc(1, sizeof(BSTree));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;

    return map;

error:
    if (map) {
        BSTree_destroy(map);
    }
    return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node)
{
    free(node);
    return 0;
}

void BSTree_destroy(BSTree *map)
{
    if (map) {
        BSTree_traverse(map, BSTree_destroy_cb);
        free(map);
    }
}

static inline BSTreeNode *BSTreeNode_create(
    BSTreeNode *parent, void *key, void *data
)
{
    BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->parent = parent;
    return node;

error:
    return NULL;
}

/*
Next, go look at `BSTree_set` and `BSTree_setnode` to see the exact
same pattern. I use `BSTree_set` to configure the initial conditions
and edge cases. A common edge case is that there's no root node, so
I have to make one to get things started.

This pattern will work with nearly any recursive algorithm you have to figure out. The way I do it is by following this pattern:

- Figure out the initial variables, how they change, and what the
  stopping conditions are for each recursive step.
- Write a recursive function that calls itself, and has arguments
  for each stopping condition and initial variable.
- Write a setup function to set initial starting conditions for the
  algorithm and handle edge cases, then have it call the recursive
  function.
- Finally, the setup function returns the final result, and possibly
  alters it if the recursive function can't handle final edge cases.
*/
static inline void BSTree_setnode(
    BSTree *map, BSTreeNode *node, void *key, void *data
)
{
    int cmp = map->compare(node->key, key);

    if (cmp <= 0) {
        if (node->left) {
            BSTree_setnode(map, node->left, key, data);
        } else {
            node->left = BSTreeNode_create(node, key, data);
        }
    } else {
        if (node->right) {
            BSTree_setnode(map, node->right, key, data);
        } else {
            node->right = BSTreeNode_create(node, key, data);
        }
    }
}

int BSTree_set(BSTree *map, void *key, void *data)
{
    if (map->root == NULL) {
        // first so just make it and get out
        map->root = BSTreeNode_create(NULL, key, data);
        check_mem(map->root);
    } else {
        BSTree_setnode(map, map->root, key, data);
    }

    return 0;
error:
    return -1;
}

/*
Before getting into how `BSTree_delete` works, I want to explain a
pattern for doing recursive function calls in a sane way. You'll
find that many tree-based data structures are easy to write if you
use recursion, but formulate a single recursive function. Part of
the problem is that you need to set up some initial data for the
first operation, then recurse into the data structure, which is hard
to do with one function.

The solution is to use two functions: One function sets up the data
structure and initial recursion conditions so that a second function
can do the real work. Take a look at `BSTree_get` first to see what
I mean.

- I have an initial condition: If `map->root` is `NULL`, then return
  `NULL` and don't recurse.
- I then setup a call to the real recursion, which is in
  `BSTree_getnode`. I create the initial condition of the root node
  to start with the key and then the `map`.
- In the `BSTree_getnode`, I then do the actual recursive logic. I
  compare the keys with `map->compare(node->key, key)` and go left,
  right, or equal to depending on the results.
- Since this function is self-similar and doesn't have to handle any
  initial conditions (because `BSTree_get` did), then I can
  structure it very simply. When it's done, it returns to the
  caller, and that return then comes back to `BSTree_get` for the
  result.
- At the end, the `BSTree_get` handles getting the `node.data`
  element but only if the result isn't `NULL`.

This way of structuring a recursive algorithm matches the way I
structure my recursive data structures. I have an initial base
function that handles initial conditions and some edge cases and
then it calls a clean recursive function that does the work. Compare
that with how I have a base structure in `BSTree` combined with
recursive `BSTreeNode` structures, which all reference each other in
a tree. Using this pattern makes it easy to deal with recursion and
keep it straight.
*/
static inline BSTreeNode *BSTree_getnode(
    BSTree *map, BSTreeNode *node, void *key
)
{
    int cmp = map->compare(node->key, key);

    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        if (node->left) {
            return BSTree_getnode(map, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if (node->right) {
            return BSTree_getnode(map, node->right, key);
        } else {
            return NULL;
        }
    }
}

void *BSTree_get(BSTree *map, void *key)
{
    if (map->root == NULL) {
        return NULL;
    } else {
        BSTreeNode *node = BSTree_getnode(map, map->root, key);
        return node == NULL ? NULL : node->data;
    }
}

static inline int BSTree_traverse_nodes(
    BSTreeNode *node, BSTree_traverse_cb traverse_cb
)
{
    int rc = 0;
    check(node != NULL, "Invalid node.");

    if (node->left) {
        rc = BSTree_traverse_nodes(node->left, traverse_cb);
        if (rc != 0)
            return rc;
    }

    if (node->right) {
        rc = BSTree_traverse_nodes(node->right, traverse_cb);
        if (rc != 0)
            return rc;
    }

    return traverse_cb(node);

error:
    return -1;
}

int BSTree_traverse(
    BSTree *map, BSTree_traverse_cb traverse_cb
)
{
    check(map != NULL, "Invalid map.");
    if (map->root) {
        return BSTree_traverse_nodes(map->root, traverse_cb);
    } else {
        return 0;
    }

error:
    return -1;
}

static inline BSTreeNode *BSTree_find_min(BSTreeNode *node)
{
    while (node->left) {
        node = node->left;
    }

    return node;
}

static inline void BSTree_replace_node_in_parent(
    BSTree *map, BSTreeNode *node, BSTreeNode *new_value
)
{
    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = new_value;
        } else {
            node->parent->right = new_value;
        }
    } else {
        // this is the root so gotta change it
        map->root = new_value;
    }

    if (new_value) {
        new_value->parent = node->parent;
    }
}

static inline void BSTree_swap(BSTreeNode *a, BSTreeNode *b)
{
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;
    temp = b->data;
    b->data = a->data;
    a->data = temp;
}

/*
This finally leads me to `BSTree_delete` and `BSTree_node_delete`.
First, you can just look at `BSTree_delete` and see that it's the
setup function. What it's doing is grabbing the resulting node data
and freeing the node that's found. Things get more complex in
`BSTree_node_delete`, because to delete a node at any point in the
tree, I have to rotate that node's children up to the parent. I'll
break this function down and the functions it uses:

...

This operation is very complex, and to be honest, I just don't
bother doing deletes in some tree data structures, and I treat them
like constant data in my software. If I need to do heavy inserting
and deleting, I use a `Hashmap` instead.
*/
static inline BSTreeNode *BSTree_node_delete(
    BSTree *map, BSTreeNode *node, void *key
)
{
    /*
    I run the compare function to figure out which direction I'm
    going.
    */
    int cmp = map->compare(node->key, key);

    /*
    This is the usual less-than branch to use when I want to go
    left. I'm handling the case that left doesn't exist here,
    and returning `NULL` to say "not found". This covers
    deleting something that isn't in the `BSTree`.
    */
    if (cmp < 0) {
        if (node->left) {
            return BSTree_node_delete(map, node->left, key);
        } else {
            // not found
            return NULL;
        }
    }

    /*
    This is the same thing but for the right branch of the tree.
    Just keep recursing down into the tree just like in the
    other functions, and return `NULL` if it doesn't exist.
    */
    else if (cmp > 0) {
        if (node->right) {
            return BSTree_node_delete(map, node->right, key);
        } else {
            // not found
            return NULL;
        }
    }

    /*
    This is where I have found the node, since the key is equal
    (`compare` returns 0).
    */
    else {

        /*
        This node has both a `left` and `right` branch, so it's
        deeply embedded in the tree.
        */
        if (node->left && node->right) {

            /*
            To remove this node, I first need to find the smallest
            node that's greater than this node, which means I call
            `BSTree_find_min` on the right child.
            */
            // swap this node for the smallest node that is bigger
            // than us
            BSTreeNode *successor = BSTree_find_min(node->right);

            /*
            Once I have this node, I'll swap its `key` and `data`
            with the current node's values. This will effectively
            take this node which was down at the bottom of the tree,
            and put its contents here, so that I don't have to try
            and shuffle the node out by its pointers.
            */
            BSTree_swap(successor, node);

            /*
            The `successor` is now this dead branch that has the
            current node's values. It could just be removed, but
            there's a chance that it has a right node value. This
            means I need to do a single rotate so that the
            successor's right node gets moved up to completely detach
            it.
            */
            // this leaves the old successor with possibly a right
            // child so replace it with that right child
            BSTree_replace_node_in_parent(
                map, successor, successor->right
            );

            /*
            At this point, the successor is removed from the tree,
            its values are replaced the current node's values, and
            any children it had are moved up into the parent. I can
            return the `successor` as if it were the `node`.
            */
            // finally it's swapped, so return successor instead of
            // node
            return successor;
        }

        /*
        At this branch, I know that the node has a left but no right,
        so I want to replace this node with its left child.
        */
        else if (node->left) {

            /*
            I again use `BSTree_replace_node_in_parent` to do the
            replace, rotating the left child up.
            */
            BSTree_replace_node_in_parent(map, node, node->left);
        }

        /*
        This branch of the `if-statement` means I have a right child
        but no left child, so I want to rotate the right child up.
        */
        else if (node->right) {

            /*
            Again, I use the function to do the rotate, but this
            time, rotate the right node.
            */
            BSTree_replace_node_in_parent(map, node, node->right);
        }

        /*
        Finally, the only thing that's left is the condition where
        I've found the node, and it has no children (no left or
        right). In this case, I simply replace this node with `NULL`
        by using the same function I did with all of the others.
        */
        else {
            BSTree_replace_node_in_parent(map, node, NULL);
        }

        /*
        After all that, I have the current node rotated out of the
        tree and replaced with some child element that will fit in
        the tree. I just return this to the caller so it can be freed
        and managed.
        */
        return node;
    }
}

void *BSTree_delete(BSTree *map, void *key)
{
    void *data = NULL;

    if (map->root) {
        BSTreeNode *node = BSTree_node_delete(map, map->root, key);

        if (node) {
            data = node->data;
            free(node);
        }
    }

    return data;
}
