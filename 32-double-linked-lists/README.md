# Exercise 32: Double Linked Lists

## Notes

- TODO
- misc
  - error when running `make`
    - fix:
      - change `#include <lcthw/list.h>` to `#include<lcthw/list.c>` in `/tests/list_tests.c`

## How To Improve It

- [ ] 1. You can make `List_clear_destroy` more efficient by using `LIST_FOREACH` and doing both `free` calls inside one loop.
  - TODO
- [ ] 2. You can add asserts for preconditions so that the program isn't given a `NULL` value for the `List *list` parameters.
  - TODO
- [ ] 3. You can add invariants that check that the list's contents are always correct, such as `count` is never `< 0`, and if `count > 0`, then `first` isn't `NULL`.
  - TODO
- [ ] 4. You can add documentation to the header file in the form of comments before each struct, function, and macro that describes what it does.
  - TODO

## Extra Credit

- [ ] ~~1. Research doubly vs. singly linked lists and when one is preferred over the other.~~
  - Skipped
- [ ] ~~2. Research the limitations of a doubly linked list. For example, while they are efficient for inserting and deleting elements, they are very slow for iterating over them all.~~
  - Skipped
- [ ] ~~3. What operations are missing that you can imagine needing? Some examples are copying, joining, and splitting. Implement these operations and write the unit tests for them.~~
  - Skipped
