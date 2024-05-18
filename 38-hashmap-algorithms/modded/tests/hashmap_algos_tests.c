#include <lcthw/bstrlib.h>
#include <lcthw/hashmap.h>
#include <lcthw/hashmap_algos.h>
#include <lcthw/darray.h>
#include "minunit.h"

/*
I then have a unit test that tests out each algorithm, but it also
tests whether it will distribute well across a number of buckets:
*/

struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");

char *test_fnv1a()
{
    uint32_t hash = Hashmap_fnv1a_hash(&test1);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_fnv1a_hash(&test2);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_fnv1a_hash(&test3);
    mu_assert(hash != 0, "Bad hash.");

    return NULL;
}

char *test_adler32()
{
    uint32_t hash = Hashmap_adler32_hash(&test1);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_adler32_hash(&test2);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_adler32_hash(&test3);
    mu_assert(hash != 0, "Bad hash.");

    return NULL;
}

char *test_djb()
{
    uint32_t hash = Hashmap_djb_hash(&test1);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_djb_hash(&test2);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_djb_hash(&test3);
    mu_assert(hash != 0, "Bad hash.");

    return NULL;
}

/*
I have the number of `BUCKETS` in this code set fairly high, since I
have a fast enough computer, but if it runs slow, just lower them
and `NUM_KEYS`. What this test lets me do is run the test, and then
look at the distribution of keys for each hash function using a bit
of analysis with a language called R.
*/
#define BUCKETS 100
#define BUFFER_LEN 20
#define NUM_KEYS (BUCKETS * 1000)
enum { ALGO_FNV1A, ALGO_ADLER32, ALGO_DJB };

/*
I do this by crafting a big list of keys using the `gen_keys`
function. These keys are taken out of the `/dev/urandom` device and
are random byte keys. I then use these keys to have the
`fill_distribution` function fill up the `stats` array with where
those keys would hash in a theoretical set of buckets. All this
function does is go through all of the keys, do the hash, then do
what the `Hashmap` would do to find its bucket.
*/
int gen_keys(DArray * keys, int num_keys)
{
    int i = 0;
    FILE *urand = fopen("/dev/urandom", "r");
    check(urand != NULL, "Failed to open /dev/urandom");
    int result = -1; // default to failure condition
    int rc = 0;

    struct bStream *stream = bsopen((bNread) fread, urand);
    check(stream != NULL, "Failed to open /dev/urandom");

    bstring key = bfromcstr("");

    // FNV1a histogram
    for (i = 0; i < num_keys; i++) {
        rc = bsread(key, stream, BUFFER_LEN);
        check(rc >= 0, "Failed to read from /dev/urandom.");

        DArray_push(keys, bstrcpy(key));
    }

    result = 0; // all good

error: // fallthrough
    if (stream) bsclose(stream);
    if (urand) fclose(urand);
    if (key) bdestroy(key);
    return result;
}

void destroy_keys(DArray * keys)
{
    int i = 0;
    for (i = 0; i < NUM_KEYS; i++) {
        bdestroy(DArray_get(keys, i));
    }

    DArray_destroy(keys);
}

void fill_distribution(
    int *stats, DArray * keys, Hashmap_hash hash_func
)
{
    int i = 0;
    uint32_t hash = 0;

    for (i = 0; i < DArray_count(keys); i++) {
        hash = hash_func(DArray_get(keys, i));
        stats[hash % BUCKETS] += 1;
    }

}

char *test_distribution()
{
    int i = 0;
    int stats[3][BUCKETS] = { {0} };
    DArray *keys = DArray_create(0, NUM_KEYS);

    mu_assert(
        gen_keys(keys, NUM_KEYS) == 0,
        "Failed to generate random keys."
    );

    fill_distribution(stats[ALGO_FNV1A], keys, Hashmap_fnv1a_hash);
    fill_distribution(
        stats[ALGO_ADLER32], keys, Hashmap_adler32_hash
    );
    fill_distribution(stats[ALGO_DJB], keys, Hashmap_djb_hash);

    /*
    Finally, I'm simply printing out a three-column table with the
    final count for each bucket, showing how many keys managed to
    get into each bucket randomly. I can then look at these numbers
    to see if the hash functions are distributing keys evenly.
    */

    fprintf(stderr, "FNV\tA32\tDJB\n");

    for (i = 0; i < BUCKETS; i++) {
        fprintf(
            stderr,
            "%d\t%d\t%d\n",
            stats[ALGO_FNV1A][i],
            stats[ALGO_ADLER32][i],
            stats[ALGO_DJB][i]
        );
    }

    destroy_keys(keys);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_fnv1a);
    mu_run_test(test_adler32);
    mu_run_test(test_djb);
    mu_run_test(test_distribution);

    return NULL;
}

RUN_TESTS(all_tests);
