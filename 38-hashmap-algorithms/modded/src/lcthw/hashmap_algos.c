#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>
#include <lcthw/dbg.h>

/*
This file then has the three hash algorithms. You should notice that
I'm just using a `bstring` for the key, but I'm using the `bchare`
function to get a character from the bstring, but returning 0 if
that character is outside the string's length.
*/

// settings taken from
// http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
const uint32_t FNV_PRIME = 16777619;
const uint32_t FNV_OFFSET_BASIS = 2166136261;

uint32_t Hashmap_fnv1a_hash(void *data)
{
    bstring s = (bstring) data;
    uint32_t hash = FNV_OFFSET_BASIS;
    int i = 0;

    for (i = 0; i < blength(s); i++) {
        hash ^= bchare(s, i, 0);
        hash *= FNV_PRIME;
    }

    return hash;
}

const int MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
    bstring s = (bstring) data;
    uint32_t a = 1, b = 0;
    int i = 0;

    for (i = 0; i < blength(s); i++) {
        a = (a + bchare(s, i, 0)) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}

uint32_t Hashmap_djb_hash(void *data)
{
    check(data != NULL, "Invalid data to hash.");

    bstring s = (bstring) data;
    uint32_t hash = 5381;
    int i = 0;

    for (i = 0; i < blength(s); i++) {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + bchare(s, i, 0);
    }

    return hash;
error:
    return 0;
}
