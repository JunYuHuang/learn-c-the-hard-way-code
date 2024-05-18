#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

/*
- This is a comparison function that the `Hashmap` uses to find
  elements by their key. It should work like all of the other
  compare functions, and it defaults to using `bstrcmp` so that
  keys are just bstrings.
*/
typedef int (*Hashmap_compare) (void *a, void *b);

/*
- This is the hashing function, and it's responsible for taking a
  key, processing its contents, and producing a single `uint32_t`
  index number. You'll see the default one soon.
*/
typedef uint32_t (*Hashmap_hash) (void *key);

/*
The structure consists of a `Hashmap` that contains any number of
`HashmapNode` structs. Looking at `Hashmap`, you can see that it's
structured like this:

- `DArarray *buckets`: A dynamic array that will be set to a fixed
  sized of 100 buckets. Each bucket will in turn contain a `DArray`
  that will hold `HashmapNode` pairs.

This almost tells you how the data is stored, but the
`buckets DArray` hasn't been created yet. Just remember that it's
kind of a two-level mapping:

- There are 100 buckets that make up the first level, and things are
  in these buckets based on their hash.
- Each bucket is a `DArray` that contains `HashmapNode` structs that
  are simply appended to the end as they're added.
*/
typedef struct Hashmap {
    DArray *buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

/*
The `HashmapNode` is then composed of these three elements:

- `void *key`: The key for this key=value pair.
- `void *data`: The value.
- `uint32_t hash`: The calculated hash, which makes finding this
  node quicker. We can just check the hash and skip any that don't
  match, only checking the key if it's equal.
*/
typedef struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb) (HashmapNode *node);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap *map, void *key, void *data);
void *Hashmap_get(Hashmap *map, void *key);

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

void *Hashmap_delete(Hashmap *map, void *key);

#endif
