/*
 * Based on code by Andre Reinald then heavily modified by Zed A.
 * Shaw.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

/*
As usual, I'm allocating all of the memory needed for the structures
defined in `radixmap.h`. I'll be using the `temp` and `contents`
later when I talk about `radix_sort`.
*/
RadixMap *RadixMap_create(size_t max)
{
    RadixMap *map = calloc(1, sizeof(RadixMap));
    check_mem(map);

    map->contents = calloc(max + 1, sizeof(RMElement));
    check_mem(map->contents);

    map->temp = calloc(max + 1, sizeof(RMElement));
    check_mem(map->temp);

    map->max = max;
    map->end = 0;

    return map;
error:
    if (map) RadixMap_destroy(map);
    return NULL;
}

/*
Again, I'm just destroying what was created.
*/
void RadixMap_destroy(RadixMap *map)
{
    if (map) {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x, y) (((uint8_t *)x)[(y)])

/*
Here's the meat of the data structure, but I'll explain what it's
doing in the next section.

A radix sort is easy to understand if you try to do it manually
first. What this algorithm does is exploit the fact that numbers are
stored with a sequence of digits that go from least significant to
most significant. It then takes the numbers and buckets them by the
digit, and when it has processed all of the digits, the numbers come
out sorted. At first it seems like magic, and honestly, looking at
the code sure seems like it is, so try doing it manually once.

To do this algorithm, write out a bunch of three digit numbers, in a
random order. Let's say we do 223, 912, 275, 100, 633, 120, and 380.

- Place the number in buckets by the ones digit:
  [380, 100, 120], [912], [633, 223], [275].
- I now have to go through each of these buckets in order, and then
  sort it by the tens digit:
  [100], [912], [120, 223], [633], [275], [380].
- Now each bucket contains numbers that are sorted the ones digit
  and then the tens digit. I need to then go through these in order  and fill in the final hundreds digit:
  [100, 120], [223, 275], [380], [633], [912].
- At this point each bucket is sorted by hundreds, tens and ones,
  and if I take each bucket in order, I get the final sorted list:
  100, 120, 223, 275, 380, 633, 912.

Make sure you do this a few times so you understand how it works.
It really is a slick little algorithm. Most importantly, it will
work on numbers of arbitrary size, so you can sort really huge
numbers because you're just doing them 1 byte at a time.

In my situation the digits (also called place values) are individual
8-bit bytes, so I need 256 buckets to store the distribution of the
numbers by their digits. I also need a way to store them such so
that I don't use too much space. If you look at `radix_sort`, you'll
see that the first thing I do is build a `count` histogram so I know
how many occurances of each digit there are for the given `offset`.

Once I know the counts for each digit (all 256 of them), I can then
use them as distribution points into a target array. For example, if
I have 10 bytes that are 0x00, then I know I can place them in the
first ten slots of the target array. This gives me an index for
where they go in the target array, which is the second `for-loop`
in `radix_sort`.

Finally, once I know where they can go in the target array, I simply
go through all of the digits in the `source` array, for this
`offset`, and place the numbers in their slots in order. Using the
`ByteOf` macro helps keep the code clean, since there's a bit of
pointer hackery to make it work. However, the end result is that all
of the integers will be placed in the bucket for their digit when
the final `for-loop` is done.

What becomes interesting is how I use this in `RadixMap_sort` to
sort these 64-bit integers by just the first 32 bits. Remember how I
have the key and value in a union for the `RMElement` type? That
means that to sort this array by the key, I only need to sort the
first 4 bytes (32 bits / 8 bits per byte) of every integer.
*/
static inline void radix_sort(
    short offset, uint64_t max, uint64_t *source, uint64_t *dest
)
{
    uint64_t count[256] = { 0 };
    uint64_t *cp = NULL;
    uint64_t *sp = NULL;
    uint64_t *end = NULL;
    uint64_t s = 0;
    uint64_t c = 0;

    // count occurences of every byte value
    for (
        sp = source, end = source + max;
        sp < end;
        sp++
    ) {
        count[ByteOf(sp, offset)]++;
    }

    // transform count into index by summing
    // elements and storing into same array
    for (s = 0, cp = count, end = count + 256; cp < end; cp++) {
        c = *cp;
        *cp = s;
        s += c;
    }

    // fill dest with the right values in the right place
    for (sp = source, end = source + max; sp < end; sp++) {
        cp = count + ByteOf(sp, offset);
        dest[*cp] = *sp;
        ++(*cp);
    }
}

/*
This uses the `radix_sort` function to actually sort the `contents`.
It does this by sorting between the `contents` and `temp` until
`contents` is sorted. You'll see how this works when I describe
`radix_sort` later.

If you look at the `RadixMap_sort`, you see that I grab a quick
pointer the `contents` and `temp` to for source and target arrays,
and then I call `radix_sort` four times. Each time I call it, I
alternate source and target, and do the next byte. When I'm done,
the `radix_sort` has done its job and the final copy has been sorted
into the `contents`.
*/
void RadixMap_sort(RadixMap *map)
{
    uint64_t *source = &map->contents[0].raw;
    uint64_t *temp = &map->temp[0].raw;

    radix_sort(0, map->end, source, temp);
    radix_sort(1, map->end, temp, source);
    radix_sort(2, map->end, source, temp);
    radix_sort(3, map->end, temp, source);
}

/*
This is using a binary search algorithm to find a key you give it.
I'll explain how this works shortly.

I'll start with how the binary search is implemented. Binary search
is a simple algorithm that most people can understand intuitively.
In fact, you could take a deck of playing cards and do this
manually. Here's how this function works, and how a binary search
is done, step by step:

- Set a high and low mark based on the size of the array.
- Get the middle element between the low and high marks.
- If the key is less-than, then the key must be below the middle.
  Set high to one less than middle.
- If the key is greater-than, then the key must be above the middle.
  Set the low mark one greater than the middle.
- If it's equal then you found it. Stop.
- Keep looping until low and high pass each other. You won't find it
  if you exit the loop.

What you're effectively doing is guessing where the key might be by
picking the middle and comparing it to the high and low marks. Since
the data is sorted, you know that the the key has to be above or
below your guess. If it's below, then you just divided the search
space in half. You keep going until you either find it or you
overlap the boundaries and exhaust the search space.
*/
RMElement *RadixMap_find(RadixMap *map, uint32_t to_find)
{
    check(map != NULL, "Invalid map.");
    check(
        map->contents != NULL, "Invalid map contents in radixmap."
    );

    int low = 0;
    int high = map->end - 1;
    RMElement *data = map->contents;

    while (low <= high) {
        int middle = low + (high - low) / 2;
        uint32_t key = data[middle].data.key;

        if (to_find < key) {
            high = middle - 1;
        } else if (to_find > key) {
            low = middle + 1;
        } else {
            return &data[middle];
        }
    }

error:  // fallthrough
    return NULL;
}

/*
Using the `RadixMap_sort` function, this will add the key and value
you request at the end, then simply sort it again so that everything
is in the right place. Once everything is sorted, the `RadixMap_find`
will work properly because it's a binary search.
*/
int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value)
{
    check(key < UINT32_MAX, "Key can't be equal to UINT32_MAX.");

    RMElement element = { .data = { .key = key, .value = value } };
    check(map->end + 1 < map->max, "RadixMap is full.");

    map->contents[map->end++] = element;

    RadixMap_sort(map);

    return 0;

error:
    return -1;
}

/*
This works the same as `RadixMap_add`, except it deletes elements of
the structure by setting their values to the max for a unsigned
32-bit integer, `UINT32_MAX`. This means that you can't use that
value as an key value, but it makes deleting elements easy. Simply
set it to that and then sort, and it'll get moved to the end. Now
it's deleted.
*/
int RadixMap_delete(RadixMap *map, RMElement *el)
{
    check(map->end > 0, "There is nothing to delete.");
    check(el != NULL, "Can't delete a NULL element.");

    el->data.key = UINT32_MAX;

    if (map->end > 1) {
        // don't bother resorting a map of 1 length
        RadixMap_sort(map);
    }

    map->end--;

    return 0;
error:
    return -1;
}
