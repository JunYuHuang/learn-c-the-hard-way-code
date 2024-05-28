/*
Ring buffers are incredibly useful when processing asynchronous I/O.
They allow one side to receive data in random intervals of random
sizes, but feed cohesive chunks to another side in set sizes or
intervals. They are a variant on the `Queue` data structure but
focus on blocks of bytes instead of a list of pointers. In this
exercise, I'm going to show you the `RingBuffer` code, and then have
you make a full unit test for it.

...

Looking at the data structure, you see I have a `buffer`, `start`,
and `end`. A `RingBuffer` does nothing more than move the `start`
and `end` around the buffer so that it loops whenever it reaches the
buffer's end. Doing this gives the illusion of an infinite read
device in a small space. I then have a bunch of macros that do
various calculations based on this.
*/

#ifndef _lcthw_RingBuffer_h
#define _lcthw_RingBuffer_h

#include <lcthw/bstrlib.h>

typedef struct {
    char *buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);

void RingBuffer_destroy(RingBuffer *buffer);

int RingBuffer_read(RingBuffer *buffer, char *target, int amount);

int RingBuffer_write(RingBuffer *buffer, char *data, int length);

int RingBuffer_empty(RingBuffer *buffer);

int RingBuffer_full(RingBuffer *buffer);

int RingBuffer_available_data(RingBuffer *buffer);

int RingBuffer_available_space(RingBuffer *buffer);

bstring RingBuffer_gets(RingBuffer *buffer, int amount);

#define RingBuffer_available_data(B) ( \
    (B)->end % (B)->length - (B)->start \
)

#define RingBuffer_available_space(B) ( \
    (B)->length - (B)->end - 1 \
)

#define RingBuffer_full(B) (RingBuffer_available_space(B) == 0)

#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)

#define RingBuffer_puts(B, D) ( \
    RingBuffer_write((B), bdata((D)), blength((D))) \
)

#define RingBuffer_get_all(B) ( \
    RingBuffer_gets((B), RingBuffer_available_data((B))) \
)

#define RingBuffer_starts_at(B) ( \
    (B)->buffer + (B)->start \
)

#define RingBuffer_ends_at(B) ( \
    (B)->buffer + (B)->end \
)

#define RingBuffer_commit_read(B, A) ( \
    (B)->start = ((B)->start + (A)) % (B)->length \
)

#define RingBuffer_commit_write(B, A) ( \
    (B)->end = ((B)->end + (A)) % (B)->length \
)

#define RingBuffer_clear(B) ( \
    RingBuffer_commit_read((B), RingBuffer_available_data((B))) \
)

#endif
