#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

/*
`THE_SIZE`: This is the variable you declared `extern` that
you'll play with from `ex22_main.c`.
*/
int THE_SIZE = 1000;

/*
`static` (file): This keyword is kind of the inverse of `extern`,
and says that the variable is only used in this .c file and
should not be available to other parts of the program. Keep in
mind that `static` at the file level (as with `THE_AGE` here) is
different than in other places.
*/
static int THE_AGE = 37;

/*
`get_age` and `set_age`: These are taking the static variable
`THE_AGE`, but exposing it to other parts of the program through
functions. You can't access `THE_AGE` directly, but these
functions can.
*/
int get_age()
{
    return THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

/*
`update_ratio`: This takes a new `ratio` value, and returns the old
one. It uses a function level static variable `ratio` to keep
track of what the ratio currently is.
*/
double update_ratio(double new_ratio)
{

    /*
    `static` (function): If you declare a variable in a function
    `static`, then that variable acts like a `static` defined in the
    file, but it's only accessible from that function. It's a way
    of creating constant state for a function, but in reality it's
    rarely used in modern C programming because they are hard to use
    with threads.
    */
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

/*
`print_size`: This prints out what `ex22.c` thinks `THE_SIZE` is
currently.
*/
void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
