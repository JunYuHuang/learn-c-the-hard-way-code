/*
This is all there is to a basic `RingBuffer` implementation. You can
read and write blocks of data to it. You can ask how much is in it
and how much space it has. There are some fancier ring buffers that
use tricks on the OS to create an imaginary infinite store, but
those aren't portable.

Since my `RingBuffer` deals with reading and writing blocks of
memory, I'm making sure that any time `end == start`, I reset them
to 0 (zero) so that they go to the beginning of the buffer. In the
Wikipedia version it isn't writing blocks of data, so it only has to
move end and `start` around in a circle. To better handle blocks,
you have to drop to the beginning of the internal buffer whenever
the data is empty.
*/

#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer *RingBuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
    buffer->length = length + 1;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = calloc(buffer->length, 1);

    return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
    if (buffer) {
        free(buffer->buffer);
        free(buffer);
    }
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    if (RingBuffer_available_data(buffer) == 0) {
        buffer->start = buffer->end = 0;
    }

    check(
        length <= RingBuffer_available_space(buffer),
        "Not enough space: %d request, %d available",
        RingBuffer_available_data(buffer), length
    );

    void *result = memcpy(RingBuffer_ends_at(buffer), data, length);
    check(result != NULL, "Failed to write data into buffer.");

    RingBuffer_commit_write(buffer, length);

    return length;
error:
    return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
    check_debug(
        amount <= RingBuffer_available_data(buffer),
        "Not enough in the buffer: has %d, needs %d",
        RingBuffer_available_data(buffer), amount
    );

    void *result = memcpy(
        target, RingBuffer_starts_at(buffer), amount
    );
    check(result != NULL, "Failed to write buffer into data.");

    RingBuffer_commit_read(buffer, amount);

    if (buffer->end == buffer->start) {
        buffer->start = buffer->end = 0;
    }

    return amount;
error:
    return -1;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
    check(
        amount > 0, "Need more than 0 for gets, you gave: %d", amount
    );
    check_debug(
        amount <= RingBuffer_available_data(buffer),
        "Not enough in the buffer."
    );

    bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);
    check(result != NULL, "Failed to create gets result.");
    check(blength(result) == amount, "Wrong result length.");

    RingBuffer_commit_read(buffer, amount);
    assert(
        RingBuffer_available_data(buffer) >= 0 &&
        "Error in read commit."
    );

    return result;
error:
    return NULL;
}
