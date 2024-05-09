#undef NDEBUG
#include "dbg.h"
#include <stdio.h>
#include <assert.h>

/*
The `copy` function is typical C code and it's the source of a huge
number of buffer overflows. It's flawed because it assumes that it
will always receive a valid, terminated C string (with `'\0'`), and
just uses a `while-loop` to process it. Problem is, to ensure that
is incredibly difficult, and if it's not handled right, it causes
the `while-loop` to loop infinitely. A cornerstone of writing solid
code is never writing loops that can possibly loop forever.
*/
/*
 * Naive copy that assumes all inputs are always valid
 * taken from K&R C and cleaned up a bit.
 */
void copy(char to[], char from[])
{
    int i = 0;

    // while loop will not end if `from` isn't '\0' terminated
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

/*
The `safercopy` function tries to solve this by requiring the caller
to give the lengths of the two strings it must deal with. By doing
this, it can make certain checks about these strings that the `copy`
function can't. It can check that the lengths are right, and that
the `to` string has enough space, and it will always terminate.
It's impossible for this function to run on forever like the `copy`
function.
*/
/*
 * A safer version that checks for many common errors using the
 * length of each string to control the loops and termination.
 */
int safercopy(int from_len, char *from, int to_len, char *to)
{
    assert(
        from != NULL && to != NULL && "'from' and 'to' can't be NULL"
    );
    int i = 0;
    int max = from_len > to_len - 1 ? to_len - 1 : from_len;

    // `to_len` must have at least 1 byte
    if (from_len < 0 || to_len <= 0)
        return -1;

    for (i = 0; i < max; i++) {
        to[i] = from[i];
    }

    to[to_len - 1] = '\0';

    return i;
}

int main (int argc, char *argv[])
{
    // careful to understand why we can get these sizes
    char from[] = "0123456789";
    int from_len = sizeof(from);

    // notice that it's 7 chars + \0
    char to[] = "0123456";
    int to_len = sizeof(to);

    debug("Copying '%s':%d to '%s':%d", from, from_len, to, to_len);

    int rc = safercopy(from_len, from, to_len, to);
    check(rc > 0, "Failed to safercopy.");
    check(to[to_len - 1] == '\0', "String not terminated.");

    debug("Result is: '%s':%d", to, to_len);

    // now try to break it
    rc = safercopy(from_len * -1, from, to_len, to);
    check(rc == -1, "safercopy should fail #1");
    check(to[to_len - 1] == '\0', "String not terminated.");

    rc = safercopy(from_len, from, 0, to);
    check(rc == -1, "safercopy should fail #2");
    check(to[to_len - 1] == '\0', "String not terminated.");

    return 0;

error:
    return 1;
}
