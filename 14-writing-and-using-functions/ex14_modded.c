#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[], int ch_len);

void print_arguments(int argc, char *argv[])
{
    int i = 0;

    // Extra Credit:
    // - Get the size of `argv[i]` with `strlen()`
    // - Pass this size to `print_letters()`
    // - Rewrite `print_letters()` to use this size to print
    for (i = 0; i < argc; i++) {
        print_letters(argv[i], strlen(argv[i]));
    }
}

void print_letters(char arg[], int ch_len)
{
    int i = 0;

    for (i = 0; i < ch_len; i++) {
        char ch = arg[i];

        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }

        // if (isalpha(ch) || isblank(ch)) {
        //     printf("'%c' == %d", ch, ch);
        // }
    }

    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha((int)ch) || isblank((int)ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
