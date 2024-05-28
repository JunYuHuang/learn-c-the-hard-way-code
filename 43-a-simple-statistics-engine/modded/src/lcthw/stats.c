#include <math.h>
#include <lcthw/stats.h>
#include <stdlib.h>
#include <lcthw/dbg.h>

/*
I'll want to load these numbers from some kind of database, and this
function lets me recreate a `Stats` struct.
*/
Stats *Stats_recreate(
    double sum, double sumsq, unsigned long n, double min, double max
)
{
    Stats *st = malloc(sizeof(Stats));
    check_mem(st);

    st->sum = sum;
    st->sumsq = sumsq;
    st->n = n;
    st->min = min;
    st->max = max;

    return st;

error:
    return NULL;
}

/*
This simple calls `Stats_recreate` with all 0 (zero) values.
*/
Stats *Stats_create()
{
    return Stats_recreate(0.0, 0.0, 0L, 0.0, 0.0);
}

/*
Using the `sum` and `n`, it gives the mean.
*/
double Stats_mean(Stats *st)
{
    return st->sum / st->n;
}

/*
This implements the formula I worked out, the only difference is
that I calculate the mean with `st->sum / st->n` in this formula
instead of calling `Stats_mean`.
*/
double Stats_stddev(Stats *st)
{
    return sqrt(
        (st->sumsq - (st->sum * st->sum / st->n)) / (st->n - 1)
    );
}

/*
This does the work of maintaining the numbers in the `Stats` struct.
When you give it the first value, it sees that `n` is 0 and sets
`min and `max` accordingly. Every call after that keeps increasing
`sum`, `sumsq`, and `n`. It then figures out if this new sample is
a new `min` or `max`.
*/
void Stats_sample(Stats *st, double s)
{
    st->sum += s;
    st->sumsq += s * s;

    if (st->n == 0) {
        st->min = s;
        st->max = s;
    } else {
        if (st->min > s)
            st->min = s;
        if (st->max < s)
            st->max = s;
    }

    st->n += 1;
}

/*
This is a simple debug function that dumps the statistics so you can
view them.
*/
void Stats_dump(Stats *st)
{
    fprintf(
        stderr,
        "sum: %f, sumsq: %f, n: %ld, "
        "min: %f, max: %f, mean: %f, stddev: %f",
        st->sum, st->sumsq, st->n, st->min, st->max, Stats_mean(st),
        Stats_stddev(st)
    );
}
