#ifndef string_algos_h
#define string_algos_h

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>

typedef struct StringScanner {
    bstring in;
    const unsigned char *haystack;
    ssize_t hlen;
    const unsigned char *needle;
    ssize_t nlen;
    size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;

/*
In order to see the effects of this skip characters list, I'm going
to make two versions of the BMH algorithm:

- This simply finds the first instance of one string in another,
  doing the entire algorithm in one shot.

*/
int String_find(bstring in, bstring what);

StringScanner *StringScanner_create(bstring in);

/*
- This uses a `StringScanner` state structure to separate the skip
  list build from the actual find. This will let me see what impact
  that has on performance. This model also gives me the advantage of
  incrementally scanning for one string in another and quickly
  finding all instances.
*/
int StringScanner_scan(StringScanner *scan, bstring tofind);

void StringScanner_destroy(StringScanner *scan);

#endif
