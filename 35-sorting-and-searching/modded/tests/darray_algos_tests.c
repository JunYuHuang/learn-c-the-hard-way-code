#include "minunit.h"
#include <lcthw/darray_algos.h>

/*
The thing to notice, and actually what tripped me up for a whole day, is the definition of `testcmp` on line 4. You have to use a
`char **` and not a `char *` because `qsort` gives you a pointer to
the pointers in the `contents` array. The function `qsort` and
friends are scanning the array, and handing pointers to each element
in the array to your comparison function. Since what I have in the
`contents` array are pointers, that means you get a pointer to a
pointer.
*/
int testcmp(char **a, char **b)
{
    return strcmp(*a, *b);
}

DArray *create_words()
{
    DArray *result = DArray_create(0, 5);
    char *words[] = {
        "asdfasfd", "werwar", "13234", "asdfasfd", "oioj"
    };
    int i = 0;

    for (i = 0; i < 5; i++) {
        DArray_push(result, words[i]);
    }

    return result;
}

int is_sorted(DArray *array)
{
    int i = 0;

    for (i = 0; i < DArray_count(array) - 1; i++) {
        if (
            strcmp(
                DArray_get(array, i), DArray_get(array, i + 1)
            ) > 0
        ) {
            return 0;
        }
    }

    return 1;
}

char *run_sort_test(
    int (*func) (DArray *, DArray_compare), const char *name
)
{
    DArray *words = create_words();
    mu_assert(!is_sorted(words), "Words should start not sorted.");

    debug("--- Testing %s sorting algorithm", name);
    int rc = func(words, (DArray_compare) testcmp);
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted(words), "didn't sort it");

    DArray_destroy(words);

    return NULL;
}

char *test_qsort()
{
    return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
    return run_sort_test(DArray_mergesort, "mergesort");
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_qsort);
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);

    return NULL;
}

RUN_TESTS(all_tests);
