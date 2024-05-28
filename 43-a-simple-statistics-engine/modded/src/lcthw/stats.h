/*
Here you can see that I've put the calculations I need to store in a
`struct`, and then I have functions for sampling and getting the
numbers. Implementing this is then just an exercise in converting
the math:
*/

#ifndef lcthw_stats_h
#define lcthw_stats_h

typedef struct Stats {
    double sum;
    double sumsq;
    unsigned long n;
    double min;
    double max;
} Stats;

Stats *Stats_recreate(
    double sum, double sumsq, unsigned long n, double min, double max
);

Stats *Stats_create();

double Stats_mean(Stats *st);

double Stats_stddev(Stats *st);

void Stats_sample(Stats *st, double s);

void Stats_dump(Stats *st);

#endif
