/*
The last thing I need to do is confirm that this math is correct.
I'm going to use numbers and calculations from my R session to
create a unit test that confirms that I'm getting the right results.
*/

#include "minunit.h"
#include <lcthw/stats.h>
#include <math.h>

const int NUM_SAMPLES = 10;
double samples[] = {
    6.1061334, 9.6783204, 1.2747090, 8.2395131, 0.3333483,
    6.9755066, 1.0626275, 7.6587523, 4.9382973, 9.5788115
};

/*
The expected results are then in a `Stats` `struct` and I simply
make sure that the number I get is close to the number R gave me.
*/
Stats expect = {
    .sumsq = 425.1641,
    .sum = 55.84602,
    .min = 0.333,
    .max = 9.678,
    .n = 10
};

double expect_mean = 5.584602;
double expect_stddev = 3.547868;

/*
There's nothing new in this unit test, except maybe the `EQ` macro.
I felt lazy and didn't want to look up the standard way to tell if
two `double` values are close, so I made this macro. The problem
with `double` is that equality assumes totally equal results, but
I'm using two different systems with slightly different rounding
errors. The solution is to say that I want the numbers to be "equal
to X decimal places."

I do this with `EQ` by raising the number to a power of 10, then
using the `round` function to get an integer. This is a simple way
to round to N decimal places and compare the results as an integer.
I'm sure there are a billion other ways to do the same thing, but
this works for now.
*/
#define EQ(X, Y, N) ( \
    round((X) * pow(10, N)) == round((Y) * pow(10, N)) \
)

char *test_operations()
{
    int i = 0;
    Stats *st = Stats_create();
    mu_assert(st != NULL, "Failed to create stats.");

    for (i = 0; i < NUM_SAMPLES; i++) {
        Stats_sample(st, samples[i]);
    }

    Stats_dump(st);

    mu_assert(EQ(st->sumsq, expect.sumsq, 3), "sumsq not valid");
    mu_assert(EQ(st->sum, expect.sum, 3), "sum not valid");
    mu_assert(EQ(st->min, expect.min, 3), "min not valid");
    mu_assert(EQ(st->max, expect.max, 3), "max not valid");
    mu_assert(EQ(st->n, expect.n, 3), "n not valid");
    mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not valid");
    mu_assert(
        EQ(expect_stddev, Stats_stddev(st), 3), "stddev not valid"
    );

    return NULL;
}

char *test_recreate()
{
    Stats *st = Stats_recreate(
        expect.sum, expect.sumsq, expect.n, expect.min, expect.max
    );

    mu_assert(st->sum == expect.sum, "sum not equal");
    mu_assert(st->sumsq == expect.sumsq, "sumsq not equal");
    mu_assert(st->n == expect.n, "n not equal");
    mu_assert(st->min == expect.min, "min not equal");
    mu_assert(st->max == expect.max, "max not equal");
    mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not valid");
    mu_assert(
        EQ(expect_stddev, Stats_stddev(st), 3), "stddev not valid"
    );

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_operations);
    mu_run_test(test_recreate);

    return NULL;
}

RUN_TESTS(all_tests);
