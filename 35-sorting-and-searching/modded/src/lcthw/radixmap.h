#ifndef _radixmap_h
#include <stdint.h>

/*
You see that I have a lot of the same operations as in a
`Dynamic Array` or a `List` data structure, but the difference is
I'm working only with fixed size 32-bit `uin32_t` integers. I'm
also introducing you to a new C concept called the `union` here.

In the `radixmap.h` file, I have the `RMElement`, union which
demonstrates using a union to convert blocks of memory between
types. In this case, I want to store a `uint64_t` sized integer for
sorting purposes, but I want two `uint32_t` integers for the data to
represent a `key` and `value` pair. By using a union, I'm able to
cleanly access the same block of memory in the two different ways I
need.
*/
typedef union RMElement {
    uint64_t raw;
    struct {
        uint32_t key;
        uint32_t value;
    } data;
} RMElement;

typedef struct RadixMap {
    size_t max;
    size_t end;
    uint32_t counter;
    RMElement *contents;
    RMElement *temp;
} RadixMap;

RadixMap *RadixMap_create(size_t max);

void RadixMap_destroy(RadixMap *map);

void RadixMap_sort(RadixMap *map);

RMElement *RadixMap_find(RadixMap *map, uint32_t key);

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value);

int RadixMap_delete(RadixMap *map, RMElement *el);

#endif
