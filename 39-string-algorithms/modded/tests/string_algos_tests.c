#include "minunit.h"
#include <lcthw/string_algos.h>
#include <lcthw/bstrlib.h>
#include <time.h>

/*
Finally, I have the unit test that first confirms that this is all
working, then it runs simple performance tests for all three,
finding algorithms in a commented out section.
*/

struct tagbstring IN_STR = bsStatic(
    "I have ALPHA beta ALPHA and oranges ALPHA"
);
struct tagbstring ALPHA = bsStatic("ALPHA");
const int TEST_TIME = 1;

char *test_find_and_scan()
{
    StringScanner *scan = StringScanner_create(&IN_STR);
    mu_assert(scan != NULL, "Failed to make the scanner.");

    int find_i = String_find(&IN_STR, &ALPHA);
    mu_assert(find_i > 0, "Failed to find 'ALPHA' in test string.");

    int scan_i = StringScanner_scan(scan, &ALPHA);
    mu_assert(scan_i > 0, "Failed to find 'ALPHA' with scan.");
    mu_assert(scan_i == find_i, "find and scan don't match");

    scan_i = StringScanner_scan(scan, &ALPHA);
    mu_assert(
        scan_i > find_i, "should find another ALPHA after the first"
    );

    scan_i = StringScanner_scan(scan, &ALPHA);
    mu_assert(
        scan_i > find_i, "should find another ALPHA after the first"
    );

    mu_assert(
        StringScanner_scan(scan, &ALPHA) == -1, "shouldn't find it"
    );

    StringScanner_destroy(scan);

    return NULL;
}

char *test_binstr_performance()
{
    int i = 0;
    int found_at = 0;
    unsigned long find_count = 0;
    time_t elapsed = 0;
    time_t start = time(NULL);

    do {
        for (i = 0; i < 1000; i++) {
            found_at = binstr(&IN_STR, 0, &ALPHA);
            mu_assert(found_at != BSTR_ERR, "Failed to find!");
            find_count++;
        }

        elapsed = time(NULL) - start;
    } while (elapsed <= TEST_TIME);

    debug(
        "BINSTR COUNT: %lu, END TIME: %d, OPS: %f",
        find_count, (int)elapsed, (double)find_count / elapsed
    );
    return NULL;
}

char *test_find_performance()
{
    int i = 0;
    int found_at = 0;
    unsigned long find_count = 0;
    time_t elapsed = 0;
    time_t start = time(NULL);

    do {
        for (i = 0; i < 1000; i++) {
            found_at = String_find(&IN_STR, &ALPHA);
            find_count++;
        }

        elapsed = time(NULL) - start;
    } while (elapsed <= TEST_TIME);

    debug(
        "FIND COUNT: %lu, END TIME: %d, OPS: %f",
        find_count, (int)elapsed, (double)find_count / elapsed
    );

    return NULL;
}

/*
The trick to notice is that I grab the starting time in `start`, and
then I loop until at least `TEST_TIME` seconds have passed. This
makes sure that I get enough samples to work with while comparing
the three. I'll then run this test with different `TEST_TIME`
settings and analyze the results.
*/
char *test_scan_performance()
{
    int i = 0;
    int found_at = 0;
    unsigned long find_count = 0;
    time_t elapsed = 0;
    StringScanner *scan = StringScanner_create(&IN_STR);

    time_t start = time(NULL);

    do {
        for (i = 0; i < 1000; i++) {
            found_at = 0;

            do {
                found_at = StringScanner_scan(scan, &ALPHA);
                find_count++;
            } while (found_at != -1);
        }

        elapsed = time(NULL) - start;
    } while (elapsed <= TEST_TIME);

    debug(
        "SCAN COUNT: %lu, END TIME: %d, OPS: %f",
        find_count, (int)elapsed, (double)find_count / elapsed
    );

    StringScanner_destroy(scan);

    return NULL;
}

/*
There's nothing amazing in this unit test; it just runs each of the
different functions in loops that last long enough to get a few
seconds of sampling. The first test (`test_find_and_scan`) just
confirms that what I've written works, because there's no point in
testing the speed of something that doesn't work. Then, the next
three functions run a large number of searches, using each of the
three functions.
*/
char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_find_and_scan);

    /*
    I have it written here with `#if 0`, which is a way to use the
    CPP to comment out a section of code. Type it in like this, and
    then remove it and the `#endif` so that you can see these
    performance tests run. As you continue with the book, simply
    comment these out so that the test doesn't waste development
    time.
    */

    // this is an idiom for commenting out sections of code
#if 0
    mu_run_test(test_scan_performance);
    mu_run_test(test_find_performance);
    mu_run_test(test_binstr_performance);
#endif

    return NULL;
}

RUN_TESTS(all_tests);
