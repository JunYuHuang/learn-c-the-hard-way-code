#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    // go thru each string in argv
    // why am I skippping argv[0]?
    for (i = 0, i += 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas", NULL
    };

    // int num_states = 4;
    int num_states = 5;

    for (i = 0; i < num_states; i++) {
        printf("state %d %s\n", i, states[i]);
    }

    // Extra Credit:
    // Assign an `states` char element to an element in `argv`
    argv[0] = states[0];

    for (i = 0; i < num_states; i++) {
        printf("state %d %s\n", i, states[i]);
    }

    for (i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    return 0;
}
