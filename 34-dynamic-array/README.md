# Exercise 34: Dynamic Array

## Notes

- dynamic arrays
  - stores an array of pointers
  - better than linked lists in most cases
  - pros (6):
    - iterate
    - index
    - destroy
    - clone
    - sort
    - large data
  - cons (3):
    - insert and remove on front (i.e. shift)
    - split or join
    - small data
- misc
  - do code review with the unit tests
    - not always finding bugs
    - finding potential bugs and misuses in code
    - creative + defensive programming
  - common error: dereference a NULL pointer
  - TODO: update `src/lcthw/hashmap.c`'s `Hashmap_set()` function
    - store result of `DArray_push()` in int `rc`
    - use `check()` macro to ensure that `rc` is not -1
  - `static inline` functions:
    - like function-like macros but cleaner and easier to write

## Extra Credit

- [ ] ~~1. Improve the unit tests to cover more of the operations, and test them using a `for-loop` to ensure that they work.~~
  - Skipped
- [ ] ~~2. Research what it would take to implement bubble sort and merge sort for DArray, but don't do it yet. I'll be implementing DArray algorithms next, so you'll do this then.~~
  - Skipped
- [ ] ~~3. Write some performance tests for common operations and compare them to the same operations in `List`. You did some of this already, but this time, write a unit test that repeatedly does the operation in question, and then in the main runner, do the timing.~~
  - Skipped
- [ ] ~~4. Look at how the `DArray_expand` is implemented using a constant increase (size + 300). Typically, dynamic arrays are implemented with a multiplicative increase (size \* 2), but I've found this to cost needless memory for no real performance gain. Test my assertion and see when you'd want a multiplicative increase instead of a constant increase.~~
  - Skipped
