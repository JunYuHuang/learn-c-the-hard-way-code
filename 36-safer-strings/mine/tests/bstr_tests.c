#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <assert.h>

// a helper function
void clean_bstring(bstring my_bstring)
{
    if (my_bstring == NULL) return;

    if (my_bstring->data) free(my_bstring->data);
    my_bstring->mlen = 0;
    my_bstring->slen = 0;
}

char *test_bfromcstr()
{
    bstring my_bstring = NULL;

    // test a NULL string
    my_bstring = bfromcstr(NULL);
    mu_assert(my_bstring == NULL, "my_bstring should be NULL.");
    clean_bstring(my_bstring);

    // test a normal string
    my_bstring = bfromcstr("Hello World!");
    mu_assert(my_bstring->slen == 12, "my_bstring slen is wrong.");
    mu_assert(my_bstring->mlen >= 12, "my_bstring mlen is wrong.");
    clean_bstring(my_bstring);

    // test an empty string
    my_bstring = bfromcstr("");
    mu_assert(my_bstring->slen == 0, "my_bstring slen is wrong.");
    mu_assert(my_bstring->mlen >= 0, "my_bstring mlen is wrong.");
    clean_bstring(my_bstring);

    // test a 1-lengthed string
    my_bstring = bfromcstr("a");
    mu_assert(my_bstring->slen == 1, "my_bstring slen is wrong.");
    mu_assert(my_bstring->mlen >= 1, "my_bstring mlen is wrong.");
    clean_bstring(my_bstring);

    return NULL;
}

char *test_blk2bstr()
{
    bstring my_bstring = NULL;

    // test a NULL string with length 1
    my_bstring = blk2bstr(NULL, 1);
    mu_assert(my_bstring == NULL, "my_bstring should be NULL.");
    clean_bstring(my_bstring);

    // test a 1-length string with length 0
    my_bstring = blk2bstr("a", 0);
    mu_assert(my_bstring->slen == 0, "my_bstring slen is wrong.");
    mu_assert(my_bstring->mlen >= 0, "my_bstring mlen is wrong.");
    clean_bstring(my_bstring);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);

    return NULL;
}

RUN_TESTS(all_tests);
