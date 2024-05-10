#include <stdio.h>
#include <ctype.h>
#include "dbg.h"
#include <string.h>

// private utility bool function (returns 1 on true or 0 on false)
int is_ok_string(const char *msg, int length)
{
    // `real_length` is possibly 8, a char pointer's byte size,
    // which is dummy  value in case `msg` is not a null-byte
    // terminated string
    size_t real_length = strnlen(msg, sizeof(msg));
    check(real_length > 0, "msg must be a null-terminated string.");
    check(length > 0, "length must be greater than zero.");

    real_length = strlen(msg);
    check(
        real_length == length,
        "length must be the count all characters in msg."
    );

    return 1;

error:
    return 0;
}

int print_a_message(const char *msg, int length)
{
    if (!is_ok_string(msg, length))
        return 1;

    printf("A STRING: %s\n", msg);

    return 0;
}

int uppercase(const char *msg, int length)
{
    if (!is_ok_string(msg, length))
        return 1;

    int i = 0;
    for (i = 0; i < length; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");

    return 0;
}

int lowercase(const char *msg, int length)
{
    if (!is_ok_string(msg, length))
        return 1;

    int i = 0;
    for (i = 0; i < length; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;
}

int fail_on_purpose(const char *msg, int length)
{
    if (!is_ok_string(msg, length))
        return 1;

    return 1;
}
