# Exercise 44: Ring Buffer

## Notes

- ring buffer
  - i.e. a fixed-sized circular array; used like an infinite array
  - how to make it
    - queue variant of bstrings OR
    - dynamic array with dynamic start and end settings
  - why?
    - fast adds + removes when the amount added and removed is random
  - uses
    - most I/O processing in C
    - get or send an unknown amount of data from 2 unlike ends
  - basic ops:
    - enqueue / write: push el to its end
    - dequeue / read: pop first el
    - full
    - empty
- misc
  - buffer: store of temp data that will be processed or copied elsewhere
    - realized as a fixed or dynamic sized array
  - first impression code review
    - like surface level code review
    - flag / comment areas in the code that may have bugs
- todos
  - [x] type-copy the source code into `./mine`
  - [x] add code comments to `./mine`
  - [x] write my own `ringbuffer_tests.c`
  - [x] read text and add notes here
  - [x] watch video and add notes here

## Extra Credit

- [ ] ~~1. Create an alternative implementation of `RingBuffer` that uses the POSIX trick and a unit test for it.~~
  - Skipped
- [ ] ~~2. Add a performance comparison test to this unit test that compares the two versions by fuzzing them with random data and random read/write operations. Make sure that you set up this fuzzing so that the same operations are done to each version, and you can compare them between runs.~~
  - Skipped
