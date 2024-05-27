# Exercise 42: Stacks and Queues

## Notes

- stacks and queues
  - can be made as wrappers / facades around double linked lists
  - stack: push & pop from one end (either front or end)
  - queue: push & pop from 2 opposing ends
    - i.e. push to end and pop from front OR
    - push to front and pop from end
- misc
  - intro to TDD
  - if doing extra credit 1,
    - it's most efficient to push / pop from end of `DArray`
- todos
  - [x] type-copy `stack_tests.c` and `queue_tests.c` in `./mine`
  - [x] write my `stack.h` to pass all tests in `stack_tests.c`
    - [x] include `list.h`
    - [x] `Stack_create()`
    - [x] `Stack_destroy()`
    - [x] `Stack_push()`: adds el to end
    - [x] `Stack_peek()`: (macro?) gets last el
    - [x] `Stack_count()` (macro?) gets stack size
    - [x] `STACK_FOREACH()`: (macro) loops thru stack
    - [x] `Stack_pop()`: remove el from end
  - [x] write my `queue.h` to pass all tests in `queue_tests.c`
    - [x] include `list.h`
    - [x] `Queue_create()`
    - [x] `Queue_destroy()`
    - [x] `Queue_send()`: push / enqueue el to end
    - [x] `Queue_peek()`: (macro?) gets first el
    - [x] `Queue_count()`: (macro?) gets queue size
    - [x] `QUEUE_FOREACH()`: (macro) loop thrus queue
    - [x] `Queue_recv()`: i.e. shift / pop first el

## Extra Credit

- [ ] ~~1. Implement `Stack` using `DArray` instead of `List`, but without changing the unit test. That means you'll have to create your own `STACK_FOREACH`.~~
  - Skipped
