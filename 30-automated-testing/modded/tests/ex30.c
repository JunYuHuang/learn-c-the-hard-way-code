/*
This includes the `minunit.h` framework.
*/
#include "minunit.h"

/*
A first test. Tests are structured so that they take no arguments
and return a `char *` that's `NULL` on success. This is important
because the other macros will be used to return an error message to
the test runner.
*/
char *test_dlopen()
{

    return NULL;
}

/*
These are more tests that are the same as the first.
*/
char *test_functions()
{

    return NULL;
}

char *test_failures()
{

    return NULL;
}

char *test_dlclose()
{

    return NULL;
}

/*
The runner function that will control all of the other tests. It has
the same form as any other test case, but it gets configured with
some additional gear.
*/
char *all_tests()
{
    /*
    This sets up some common stuff for a test with `mu_suite_start`.
    */
    mu_suite_start();

    /*
    This is how you say what tests to run, using the `mu_run_test`
    macro.
    */
    mu_run_test(test_dlopen);
    mu_run_test(test_functions);
    mu_run_test(test_failures);
    mu_run_test(test_dlclose);

    /*
    After you say what tests to run, you then return `NULL` just
    like a normal test function.
    */
    return NULL;
}

/*
Finally, you just use the big `RUN_TESTS` macro to wire up the
`main` method with all of the goodies, and tell it to run the
`all_tests` starter.
*/
RUN_TESTS(all_tests);
