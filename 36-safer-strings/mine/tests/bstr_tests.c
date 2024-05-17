#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <assert.h>

static char *p_cstring = NULL;
static bstring *p_bstring = NULL;

// TODO
char *test_bfromcstr()
{
    // TODO
    p_bstring = bfromcstr(p_cstring);
    mu_assert(p_bstring == NULL, "bstring should be NULL.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    // TODO
    mu_run_test(test_bfromcstr);

    return NULL;
}

RUN_TESTS(all_tests);
