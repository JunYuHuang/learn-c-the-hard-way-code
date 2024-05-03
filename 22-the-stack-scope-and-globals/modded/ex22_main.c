#include "ex22.h"
#include "dbg.h"

/*
A `const`, which stands for constant, and is an alternative to
using a `define` to create a constant variable.
*/
const char *MY_NAME = "Zed A. Shaw";

/*
A simple function that demonstrates more scope issues in a function.
*/
void scope_demo(int count)
{

    /*
    This prints out the value of `count` as it is at the top of the
    function.
    */
    log_info("count is: %d", count);

    /*
    An `if-statement` that starts a new scope block, and then
    has another `count` variable in it. This version of `count`
    is actually a whole new variable. It's kind of like the
    `if-statement` started a new mini function.
    */
    if (count > 10) {

        /*
        The `count` that is local to this block is actually
        different from the one in the function's parameter list.
        */
        int count = 100;    // BAD! BUGS!

        /*
        This prints it out so you can see it's actually 100
        here, not what was passed to `scope_demo`.
        */
        log_info("count in this scope is %d", count);
    }

    /*
    Now for the freaky part. You have `count` in two places: Now
    for the freaky part. You have `count` in two places: the
    parameters to this function, and in the `if-statement`. The
    `if-statement` created a new block, so the `count` on line 11
    does not impact the parameter with the same name. This line
    prints it out, and you'll see that it prints the value of the
    parameter, not 100.
    */
    log_info("count is at exit: %d", count);

    /*
    Then, I set the parameter count to 3000 and print that out, which will demonstrate that you can change function parameters and they don't impact the caller's version of the variable.
    */
    count = 3000;

    log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    // test out THE_AGE accessors

    /*
    This prints out the current values of `MY_NAME`, and gets
    `THE_AGE` from `ex22.c` by using the accessor function
    `get_age`.
    */
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    /*
    This uses `set_age` in `ex22.c` to change `THE_AGE` and
    then print it out.
    */
    set_age(100);

    log_info("My age is now: %d", get_age());

    // test out THE_SIZE extern

    /*
    Then I do the same thing to `THE_SIZE` from `ex22.c`, but this
    time I'm accessing it directly. I'm also demonstrating that
    it's actually changing in that file by printing it here and
    with `print_size`.
    */
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio function static

    /*
    Here, I show how the static variable `ratio` inside
    `update_ratio` is maintained between function calls.
    */
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    /*
    Finally, I'm running `scope_demo` a few times so you can see
    the scope in action. The big thing to notice is that the local
    `count` variable remains unchanged. You must understand that
    passing in a variable like this won't let you change it in the
    function. To do that, you need our old friend the pointer. If
    you were to pass a pointer to this `count`, then the called
    function would have the address of it and could change it.
    */
    // test the scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    return 0;
}
