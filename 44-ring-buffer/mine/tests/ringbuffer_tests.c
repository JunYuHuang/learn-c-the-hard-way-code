/*
For your unit test, you'll want to test as many possible conditions
as you can. The easiest way to do that is to preconstruct different
`RingBuffer` structs, and then manually check that the functions and
math work right. For example, you could make one where `end` is
right at the end of the buffer and `start` is right before the
buffer, and then see how it fails.
*/

#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <string.h>

#define BUFFER_SIZE 3
#define TARGET_SIZE 99

static RingBuffer *ringbuffer = NULL;
static char target[TARGET_SIZE];

char *test_create()
{
    ringbuffer = RingBuffer_create(BUFFER_SIZE);
    mu_assert(ringbuffer != NULL, "RingBuffer_create failed");
    mu_assert(
        ringbuffer->buffer != NULL,
        "buffer should not be NULL"
    );
    mu_assert(
        ringbuffer->length == BUFFER_SIZE + 1, "length is wrong"
    );
    mu_assert(ringbuffer->start == 0, "start is wrong");
    mu_assert(ringbuffer->end == 0, "end is wrong");

    return NULL;
}

char *test_read_write()
{
    int rc = -1;

    // test writing data whose size equals the buffer
    rc = RingBuffer_write(ringbuffer, "123", 3);
    mu_assert(rc != -1, "Failed to write data to buffer.");
    mu_assert(ringbuffer->start == 0, "start is wrong");
    mu_assert(ringbuffer->end == 3, "end is wrong");
    mu_assert(
        strncmp(ringbuffer->buffer, "123", 3) == 0,
        "buffer is wrong"
    );

    // test writing data that should not write to the buffer
    rc = RingBuffer_write(ringbuffer, "4", 1);
    mu_assert(rc == -1, "Should fail to write data to buffer.");
    mu_assert(ringbuffer->start == 0, "start is wrong");
    mu_assert(ringbuffer->end == 3, "end is wrong");
    mu_assert(
        strncmp(ringbuffer->buffer, "123", 3) == 0,
        "buffer is wrong"
    );

    // test reading data whose size is greater than the amount
    // of data stored in the buffer
    rc = RingBuffer_read(ringbuffer, target, 4);
    mu_assert(rc == -1, "Should fail to read data from buffer.");
    mu_assert(ringbuffer->start == 0, "start is wrong");
    mu_assert(ringbuffer->end == 3, "end is wrong");
    mu_assert(
        strncmp(ringbuffer->buffer, "123", 3) == 0,
        "buffer is wrong"
    );

    // test reading data whose size is less than the amount of
    // data stored in the buffer
    rc = RingBuffer_read(ringbuffer, target, 2);
    mu_assert(rc != -1, "Failed to read data from buffer.");
    mu_assert(ringbuffer->start == 2, "start is wrong");
    mu_assert(ringbuffer->end == 3, "end is wrong");
    mu_assert(
        strncmp(target, "12", 2) == 0,
        "target (read buffer) is wrong"
    );

    return NULL;
}

char *test_destroy()
{
    RingBuffer_destroy(ringbuffer);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
