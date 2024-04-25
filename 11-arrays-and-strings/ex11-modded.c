#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int numbers[4] = { 0 };
    // char name[4] = { 'a' };
    char name[4] = { 'a', 'a', 'a', 'a' };
    // char name[4];
    // char *name = "aaaa";

    // first, print them out raw
    printf(
      "numbers: %d %d %d %d\n",
      numbers[0],
      numbers[1],
      numbers[2],
      numbers[3]
    );

    printf(
      "name each: %c %c %c %c\n",
      name[0], name[1], name[2], name[3]
    );

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    // numbers[0] = 'p';
    // numbers[1] = 'r';
    // numbers[2] = 'o';
    // numbers[3] = 'p';

    // setup the name;
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';
    // name[3] = 'A';
    // name[0] = 1;
    // name[1] = 3;
    // name[2] = 3;
    // name[3] = 7;

    // then print them out initialized
    printf(
      "numbers: %d %d %d %d\n",
      numbers[0],
      numbers[1],
      numbers[2],
      numbers[3]
    );

    printf(
      "name each: %c %c %c %c\n",
      name[0], name[1], name[2], name[3]
    );

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf(
      "another each: %c %c %c %c\n",
      another[0],
      another[1],
      another[2],
      another[3]
    );

    // Extra Credit:
    // > Treat a 4-byte sized char array (string)
    // as an 4-byte sized integer
    //
    // - copy data from the int to the memory address of the string
    // using `memcpy` from `<string.h>`?
    char my_name[4] = { 'r', 'e', 'e', '\0' };
    int my_int = 69;

    printf("sizeof my_name: %ld\n", sizeof my_name);
    printf("sizeof my_int: %ld\n", sizeof my_int);
    int copy_res = memcpy(my_name, my_int, sizeof my_int);

    char *msg = (copy_res == 0) ? "memcpy() OK" : "memcpy() FAILED";
    puts(msg);
    // int result = my_name + 1;
    // printf("my_name: %d", my_name);
    // printf("my_int: %d", my_int);
    // printf("my_name + my_int = %d", result);

    return 0;
}
