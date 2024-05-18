#undef NDEBUG
#include <stdint.h>
#include <lcthw/hashmap.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>

/*
There's nothing very complicated in the implementation, but the
`default_hash` and `Hashmap_find_bucket` functions will need some
explanation. When you use `Hashmap_create`, you can pass in any
compare and hash functions you want, but if you don't, it uses the
`default_compare` and `default_hash` functions.
*/

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring) a, (bstring) b);
}

/*
The first thing to look at is how `default_hash` does its thing.
This is a simple hash function called a Jenkins hash after Bob
Jenkins. I got the algorithm from the "Jenkins hash" page on
Wikipedia. It simply goes through each byte of the key to hash (a
bstring), and then it works the bits so that the end result is a
single `uint32_t`. It does this with some adding and exclusive or
(XOR) operations.
*/
/**
 * Simple Bob Jenkins's hash algorithm taken from the
 * wikipedia description.
 */
static uint32_t default_hash(void *a)
{
    size_t len = blength((bstring) a);
    char *key = bdata((bstring) a);
    uint32_t hash = 0;
    uint32_t i = 0;

    for (hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash)
{
    Hashmap *map = calloc(1, sizeof(Hashmap));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;
    map->hash = hash == NULL ? default_hash : hash;
    map->buckets = DArray_create(
        sizeof(DArray *), DEFAULT_NUMBER_OF_BUCKETS
    );
    check_mem(map->buckets);
    map->buckets->end = map->buckets->max;  // fake out expanding it

    return map;

error:
    if (map) {
        Hashmap_destroy(map);
    }

    return NULL;
}

void Hashmap_destroy(Hashmap *map)
{
    int i = 0;
    int j = 0;

    if (map) {
        if (map->buckets) {
            for (i = 0; i < DArray_count(map->buckets); i++) {
                DArray *bucket = DArray_get(map->buckets, i);
                if (bucket) {
                    for (j = 0; j < DArray_count(bucket); j++) {
                        free(DArray_get(bucket, j));
                    }
                    DArray_destroy(bucket);
                }
            }
            DArray_destroy(map->buckets);
        }

        free(map);
    }
}

static inline HashmapNode *Hashmap_node_create(
    int hash, void *key, void *data
)
{
    HashmapNode *node = calloc(1, sizeof(HashmapNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;

error:
    return NULL;
}

/*
There are many different hash functions, all with different
properties, but once you have one, you need a way to use it to find
the right buckets. The `Hashmap_find_bucket` does it like this:

- First, it calls `map->hash(key)` to get the hash for the key.
- It then finds the bucket using `hash % DEFAULT_NUMBER_OF_BUCKETS`,
  so every hash will always find some bucket no matter how big it is.
- It then gets the bucket, which is also a `DArray`, and if it's not
  there, it will create the bucket. However, that depends on if the
`create` variable says to do so.
- Once it has found the `DArray` bucket for the right hash, it
  returns it, and the `hash_out` variable is used to give the caller
  the hash that was found.

All of the other functions then use `Hashmap_find_bucket` to do
their work:

- Setting a key/value involves finding the bucket, making a
  `HashmapNode`, and then adding it to the bucket.
- Getting a key involves finding the bucket, and then finding the
  `HashmapNode` that matches the `hash` and `key` that you want.
- Deleting an item finds the bucket, finds where the requested node
  is, and then removes it by swapping the last node into its place.
*/
static inline DArray *Hashmap_find_bucket(
    Hashmap *map, void *key, int create, uint32_t *hash_out
)
{
    check(map != NULL, "Invalid map given.");

    uint32_t hash = map->hash(key);
    int bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS;
    check(bucket_n >= 0, "Invalid bucket found: %d", bucket_n);
    // store it for the return so the caller can use it
    *hash_out = hash;

    DArray *bucket = DArray_get(map->buckets, bucket_n);

    if (!bucket && create) {
        // new bucket, set it up
        bucket = DArray_create(
            sizeof(void *), DEFAULT_NUMBER_OF_BUCKETS
        );
        check_mem(bucket);
        DArray_set(map->buckets, bucket_n, bucket);
    }

    return bucket;

error:
    return NULL;
}

int Hashmap_set(Hashmap *map, void *key, void *data)
{
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 1, &hash);
    check(bucket, "Error can't create bucket.");

    HashmapNode *node = Hashmap_node_create(hash, key, data);
    check_mem(node);

    DArray_push(bucket, node);

    return 0;

error:
    return -1;
}

static inline int Hashmap_get_node(
    Hashmap *map, uint32_t hash, DArray *bucket, void *key
)
{
    int i = 0;
    check(map != NULL, "Invalid map.");
    check(bucket != NULL, "Invalid bucket.");

    for (i = 0; i < DArray_end(bucket); i++) {
        debug("TRY: %d", i);
        HashmapNode *node = DArray_get(bucket, i);
        if (
            node->hash == hash &&
            map->compare(node->key, key) == 0
        ) {
            return i;
        }
    }

error:  // fallthrough
    return -1;
}

void *Hashmap_get(Hashmap *map, void *key)
{
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1) return NULL;

    HashmapNode *node = DArray_get(bucket, i);
    check(
        node != NULL,
        "Failed to get node from bucket when it should exist."
    );
    return node->data;

error:          // fallthrough
    return NULL;
}

/*
The only other function that you should study is the
`Hashmap_traverse`. This simply walks through every bucket, and for
any bucket that has possible values, it calls the `traverse_cb` on
each value. This is how you scan a whole `Hashmap` for its values.
*/
int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb)
{
    int i = 0;
    int j = 0;
    int rc = 0;

    for (i = 0; i < DArray_count(map->buckets); i++) {
        DArray *bucket = DArray_get(map->buckets, i);
        if (bucket) {
            for (j = 0; j < DArray_count(bucket); j++) {
                HashmapNode *node = DArray_get(bucket, j);
                rc = traverse_cb(node);
                if (rc != 0)
                    return rc;
            }
        }
    }

    return 0;
}

void *Hashmap_delete(Hashmap *map, void *key)
{
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket)
        return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1)
        return NULL;

    HashmapNode *node = DArray_get(bucket, i);
    void *data = node->data;
    free(node);

    HashmapNode *ending = DArray_pop(bucket);

    if (ending != node) {
        // alright looks like it's not the last one, swap it
        DArray_set(bucket, i, ending);
    }

    return data;
}
