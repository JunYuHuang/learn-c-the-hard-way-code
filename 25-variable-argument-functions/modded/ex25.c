/*
This program is similar to the previous exercise, except I have
written my own `scanf` function that to handle strings the way I
want. The main function should be clear to you, as well as the two
functions `read_string` and `read_int`, since they do nothing new.
*/

/** WARNING: This code is fresh and potentionally isn't correct yet. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
    *out_string = calloc(1, max_buffer + 1);
    check_mem(*out_string);

    char *result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "Input error.");

    return 0;

error:
    if (*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int *out_int)
{
    char *input = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number");

    *out_int = atoi(input);

    free(input);
    return 0;

error:
    if (input) free(input);
    return -1;
}

/*
The varargs function is called `read_scan`, and it does the same
thing that `scanf` is doing using the `va_list` data structure and
it supporting macros and functions. Here's how:

I set as the last parameter of the function the keyword `...` to
indicate to C that this function will take any number of arguments
after the `fmt` argument. I could put many other arguments before
this, but I can't put anymore after this.
*/
int read_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    /*
    After setting up some variables, I create a `va_list` variable
    and initialize it with `va_start`. This configures the gear in
    `stdarg.h` that handles variable arguments.
    */
    va_list argp;
    va_start(argp, fmt);

    /*
    I then use a `for-loop` to loop through the format string `fmt`
    and process the same kind of formats that `scanf` has, only much
    simpler. I just have integers, characters, and strings.
    */
    for (i = 0; fmt[i] != '\0'; i++) {

        /*
        When I hit a format, I use the `switch-statement` to figure
        out what to do.
        */
        if (fmt[i] == '%') {
            i++;
            switch (fmt[i]) {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;
                case 'd':

                    /*
                    Now, to get a variable from the `va_list argp`,
                    I use the macro `va_arg(argp, TYPE`) where
                    `TYPE` is the exact type of what I will assign
                    this function parameter to. The downside to this
                    design is you're flying blind, so if you don't
                    have enough parameters, then oh well, you'll
                    most likely crash.
                    */
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int");
                    break;
                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;

                /*
                The interesting difference from `scanf` is I'm
                assuming that people want `read_scan` to create
                the strings it reads when it hits a `'s'` format
                sequence. When you give this sequence, the
                function takes two parameters off the
                `va_list argp` stack: the max function size to
                read, and the output character string pointer.
                Using that information it just runs
                `read_string` to do the real work.

                This makes `read_scan` more consistent than `scanf`,
                since you always give an address-of `&` on variables
                to have them set appropriately.
                */
                case 's':
                    max_buffer = va_arg(argp, int);
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string, max_buffer);
                    check(rc == 0, "Failed to read string.");
                    break;

                /*
                Finally, if the function encounters a character
                that's not in the correct format, it just reads one
                char to skip it. It doesn't care what that char is,
                just that it should skip it.
                */
                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }

        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main(int argc, char *argv[])
{
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "Failed first name.");

    printf("What's your initial? ");
    rc = read_scan("%c\n", &initial);
    check(rc == 0, "Failed initial.");

    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed last name.");

    printf("How old are you? ");
    rc = read_scan("%d", &age);
    check(rc == 0, "Failed to read age.");

    printf("---- RESULTS ----\n");
    printf("First Name: %s", first_name);
    printf("Initial: '%c'\n", initial);
    printf("Last Name: %s", last_name);
    printf("Age: %d\n", age);

    free(first_name);
    free(last_name);
    return 0;
error:
    return -1;
}
