/*
The usual start of a C program.
*/
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{

    /*
    Declare an `int`, `float`, and `double` for some fake
    calculations.
    */
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;

    /*
    Declare some character data. First a single character,
    then two characte array strings.
    */
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    /*
    Use `printf` to print out each of these declared variables.
    */
    printf("You are %d miles away,\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf(
        "My whole name is %s %c. %s.\n",
        first_name,
        initial,
        last_name
    );

    /*
    Declare an integer and a double variable to show you don't
    have to declare variables at the top of a function.
    */
    int bugs = 100;
    double bug_rate = 1.2;

    /*
    Print these variables using `printf` again.
    */
    printf(
        "You have %d bugs at the imaginary rate of %f.\n",
        bugs,
        bug_rate
    );

    /*
    Calculate a really large number using a `long` integer
    type. Notice the use of `L` notation to specify long
    integer constants (1L, 1024L).
    */
    long universe_of_defects = 1L * 1024L * 1024L * 1024L;
    printf(
        "The entire universe has %ld bugs.\n",
        universe_of_defects
    );

    // Extra Credit: make `long` to `unsigned long`
    // and find the number that makes it too big
    unsigned long big_long = ULONG_MAX + 1L;
    printf("sizeof unsigned long: %lu.\n", sizeof(unsigned long));
    printf("`big_long` value: %lu\n", big_long);

    /*
    Print out some calculations and math using the variables we
    have.
    */
    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf(
        "That is only a %e portion of the universe.\n",
        part_of_universe
    );

    /*
    This is actually not good form, but demonstrate that C will
    let you use `char` variables in math expressions by multiplying
    a `char` by an `int`, then print it.
    */
    // this makes no sense, just a demo of something weird
    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    printf("Which means you should care %d%%.\n", care_percentage);

    /*
    The end of the `main` function.
    */
    return 0;
}
