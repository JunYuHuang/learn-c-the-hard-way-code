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

/*
Before getting into how `BSTree_delete` works, I want to explain a pattern for doing recursive function calls in a sane way. You'll find that many tree-based data structures are easy to write if you use recursion, but forumlate a single recursive function. Part of the problem is that you need to set up some initial data for the first operation, then recurse into the data structure, which is hard to do with one function.

The solution is to use two functions: One function sets up the data structure and initial recursion conditions so that a second function can do the real work. Take a look at `BSTree_get` first to see what I mean.

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
that with how I have a base structure in `BStree` combined with
recursive `BSTreeNode` structures, which all reference each other in
a tree. Using this pattern makes it easy to deal with recursion and
keep it straight.
*/
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
}

int BSTree_traverse(
    BSTree *map, BSTree_traverse_cb traverse_cb
)
{
    if (map->root) {
        return BSTree_traverse_nodes(map->root, traverse_cb);
    }

    return 0;
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

    if (cmp < 0) {

        /*
        This is the usual less-than branch to use when I want to go
        left. I'm handling the case that left doesn't exist here,
        and returning `NULL` to say "not found." This covers
        deleting something that isn't in the `BSTree`.
        */
        if (node->left) {
            return BSTree_node_delete(map, node->left, key);
        } else {
            // not found
            return NULL;
        }
    } else if (cmp > 0) {
        if (node->right) {
            return BSTree_node_delete(map, node->right, key);
        } else {
            // not found
            return NULL;
        }
    } else {
        if (node->left && node->right) {
            // swap this node for the smallest node that is bigger
            // than us
            BSTreeNode *successor = BSTree_find_min(node->right);
            BSTree_swap(successor, node);

            // this leaves the old successor with possibly a right
            // child so replace it with that right child
            BSTree_replace_node_in_parent(
                map, successor, successor->right
            );

            // finally it's swapped, so return successor instead of
            // node
            return successor;
        } else if (node->left) {
            BSTree_replace_node_in_parent(map, node, node->left);
        } else if (node->right) {
            BSTree_replace_node_in_parent(map, node, node->right);
        } else {
            BSTree_replace_node_in_parent(map, node, NULL);
        }

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
