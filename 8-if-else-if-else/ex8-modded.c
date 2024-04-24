#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc < 2) {
        printf("You have no arguments. You suck.\n");
    } else if (argc == 2) {
        printf("You only have one argument. You suck.\n");
    }

    /*
    Swapping `&&` for `||` makes it so that:
    - The second conditional check (`argc < 4`) never runs.
    - The last `else` clause never runs.
    */
    else if (argc > 2 || argc < 4) {
        printf("Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    /*
    This conditional never runs because of the previous conditional.
    */
    else if (argc >= 4) {
        printf("You have too many arguments. You Suck.\n");
    }

    return 0;
}
