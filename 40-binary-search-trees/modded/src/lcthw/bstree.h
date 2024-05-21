#ifndef _lcthw_BSTree_h
#define _lcthw_BSTree_h

typedef int (*BSTree_compare) (void *a, void *b);

typedef struct BSTreeNode {
    void *key;
    void *data;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
} BSTreeNode;

/*
This follows the same pattern that I've been using this whole time
where I have a base container named `BSTree`, which has nodes named
`BSTreeNode` that make up the actual contents. Bored yet? Good,
there's no reason to be clever with this kind of structure.
*/
typedef struct BSTree {
    int count;
    BSTree_compare compare;
    BSTreeNode *root;
} BSTree;

typedef int (*BSTree_traverse_cb) (BSTreeNode *node);

BSTree *BSTree_create(BSTree_compare compare);
void BSTree_destroy(BSTree *map);

/*
That's all there is to `get`, so now on to `set`. It's nearly the
same thing, except you're looking for where to put a new node:

- If there is no `BSTree.root`, then I just make it and we're done.
  That's the first node.
- After that, I compare your key to `node.key`, starting at the root.

- If your key is less than or equal to the `node.key`, then I want
  to go left. If your key is greater than and not equal to the `node.
  key`, then I want to go right.
- I keep repeating step 3 until I reach a node where left or right
  doesn't exist, but that's the direction I need to go.
- Once there, I set that direction (left or right) to a new node for
  the key and data I want, and then set this new node's parent to the previous node I came from. I'll use the parent node when I do
  delete.

This also makes sense given how get works. If finding a node
involves going left or right depending on how the key compares, then
setting a node involves the same thing until I can set the left or
right for a new node.
*/
int BSTree_set(BSTree *map, void *key, void *data);

/*
The important thing is how the `BSTreeNode` is configured, and how
it gets used to do each operation: set, get, and delete. I'll cover
get first since it's the easiest operation, and I'll pretend I'm
doing it manually against the data structure:

- I take the key you're looking for and I start at the root. First
  thing I do is compare your key with that node's key.
- If your key is less than the `node.key`, then I traverse down the
  tree using the `left` pointer.
- If your key is greater than the `node.key`, then I go down with
  `right`.
- I repeat steps 2 and 3 until I either find a matching node.key or
  get to a node that has no left and right. In the first case, I
  return the `node.data`. In the second, I return `NULL`.
*/
void *BSTree_get(BSTree *map, void *key);

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb);

void *BSTree_delete(BSTree *map, void *key);

#endif
