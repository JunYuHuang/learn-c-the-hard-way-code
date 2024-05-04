#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int print_int(int *input_int, int max_buffer)
{
    char *output_string = calloc(1, max_buffer + 1);
    check_mem(output_string);

    sprintf(output_string, "%d", *input_int);
    fputs(output_string, stdout);

    free(output_string);

    return 0;

error:
    if (output_string) free(output_string);
    output_string = NULL;
    return -1;
}

// my own `printf()`
int print_format(const char *format, ...)
{
    // `rc` means "return code"
    int rc = 0;

    char *input_char = NULL;
    char **input_string = NULL;
    int *input_int = NULL;

    va_list arg_params;
    va_start(arg_params, format);

    int i = 0;
    for (i = 0; format[i] != '\0'; i++) {
        char ch = format[i];

        // print escaped chars
        if (ch == '\\') {
            i++;
            ch = format[i];
            switch(ch) {
                case 'n':
                    fputc('\n', stdout);
                    break;
                case '\"':
                    fputc('\"', stdout);
                    break;
                default:
                    sentinel("Invalid escaped character.");
            }
            continue;
        }

        // print char normally if no format specifier
        if (ch != '%') {
            fputc(ch, stdout);
            continue;
        }

        // print string with format specifier
        i++;
        ch = format[i];
        switch(ch) {
            case 'c':
                input_char = va_arg(arg_params, char *);
                fputc(*input_char, stdout);
                break;
            case 's':
                input_string = va_arg(arg_params, char **);
                fputs(*input_string, stdout);
                break;
            case 'd':
                input_int = va_arg(arg_params, int *);
                rc = print_int(input_int, MAX_DATA);
                check(rc == 0, "Failed to print int.");
                break;
            case '\0':
                sentinel("Invalid format, you ended with %%.");
                break;
            default:
                sentinel("Invalid format.");
        }

        // TODO - check for end-of-file or error?
    }

    va_end(arg_params);
    return 0;

error:
    va_end(arg_params);
    return -1;
}

int main(int argc, char *argv[])
{
    int rc = 0;
    char my_char = '@';
    char *my_string = "Hello, World!";
    int my_int = 420;
    int my_ints[] = { 1, 3, 3, 7 };

    rc = print_format(
        "string with no format spec and no escape char"
    );
    check(rc == 0, "Failed to print a plain string");

    rc = print_format("\nstring with 2 escape chars \n");
    check(rc == 0, "Failed to print a string with an escape char");

    rc = print_format("my_char: '%c'\n", &my_char);
    check(
        rc == 0,
        "Failed to print a string with a char format spec"
    );

    rc = print_format("my_string: \"%s\"\n", &my_string);
    check(
        rc == 0,
        "Failed to print a string with a string format spec"
    );

    rc = print_format("my_int: %d\n", &my_int);
    check(
        rc == 0,
        "Failed to print a string with an int format spec"
    );

    rc = print_format(
        "string with different formats: %d, '%c', \"%s\" !!\n",
        &my_int, &my_char, &my_string
    );
    check(
        rc == 0,
        "Failed to print a string with different format specs"
    );

    rc = print_format(
        "my_ints[]: [ %d, %d, %d, %d ]\n",
        &my_ints[0],
        &my_ints[1],
        &my_ints[2],
        &my_ints[3]
    );
    check(
        rc == 0,
        "Failed to print a string with 1+ int format specs"
    );

    return 0;

error:
    return -1;
}
