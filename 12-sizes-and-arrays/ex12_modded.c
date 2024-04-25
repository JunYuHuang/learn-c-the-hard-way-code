#include <stdio.h>

int main(int argc, char *argv[])
{
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w'
    };

    // Extra Credit: assign elements to `areas` array
    // areas[0] = 100;

    // Extra Credit: assign to elements of `name`
    // name[0] = 'B';
    // name[4] = 'M';

    // Extra Credit: assign to elements of `full_name`
    // full_name[4] = 'G';
    // full_name[-1] = '@';

    // Extra Credit: set an element of `areas` to a char from `name`
    areas[2] = name[0];

    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf(
        "The number of ints in areas: %ld\n",
        sizeof(areas) / sizeof(int)
    );
    printf(
      "The first area is %d, the 2nd %d.\n", areas[0], areas[1]
    );

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf(
        "The number of chars: %ld\n",
        sizeof(name) / sizeof(char)
    );

    printf(
        "The size of full name (char[]): %ld\n",
        sizeof(full_name)
    );
    printf(
        "The number of chars: %ld\n",
        sizeof(full_name) / sizeof(char)
    );

    // full_name[12] = 'X';

    printf(
        "name=\"%s\" and full_name=\"%s\"\n", name, full_name
    );

    return 0;
}
