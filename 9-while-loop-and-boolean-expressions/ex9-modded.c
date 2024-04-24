#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 25;
    while (i > -1) {
        printf("%d\n", i);
        i--;
    }

    // Extra Credit: a more complex while loop
    int j = 0;
    while (j <= 10) {
        // skip printing even numbers
        if (j % 2 == 0) {
            j++;
            continue;
        }

        // only prints odd numbers
        printf("%d, ", j);
        j++;
    }
    printf("\n");

    return 0;
}
