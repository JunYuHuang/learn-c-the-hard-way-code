# Exercise 7: Variables and Types

## Notes

- floats vs double
  - float is smaller
- char: only ONE char in single quotes
- `%ld`: render a long decimal in `printf()`
- C has type promotion system that implicitly converts different types together
- off by 1 is a common error
- unsigned: doubles int range but only for non-negative ints
- null byte: ends strings in C

## Extra Credit

- [x] Make the number you assign to `universe_of_defects` various sizes until you get a warning from the compiler.

  ```c
  long universe_of_defects = 9999999999999999999L;
  ```

- [x] What do these really huge numbers actually print out?

  ```c
  double super_power = 56789.4532;
  // -> 56789.453200

  long universe_of_defects = 1L * 1024L * 1024L * 1024L;
  // -> 1073741824

  double expected_bugs = 100 * 1.2;
  // -> 120.000000

  double part_of_universe = expected_bugs / universe_of_defects;
  // -> 1.117587e-07 (~0.0083333)
  ```

- [x] Change `long` to `unsigned long` and try to find the number that makes it too big.

  - see https://stackoverflow.com/questions/54813967/what-is-the-exact-value-range-for-unsigned-long

  ```c
  #include <limits.h>

  // ...

  unsigned long big_long = ULONG_MAX + 1L;
  // ULONG_MAX -> 18446744073709551615
  // big_long -> 0
  ```

- [x] Go search online to find out what `unsigned` does.
  - `signed` allows both negative and positive numbersy
  - `unsigned`:
    - short for unsigned integer
    - doubles the value range for an integer at the cost of only allowing non-negative integers (i.e. only allows values from 0 and up)
- [x] Try to explain to yourself (before I do in the next exercise) why you can multiply a `char` and an `int`.
  - TLDR: because of implicit type casting / conversion in C
  - can do math on numbers
  - an integer is a kind of number
  - thus, can do math on integers
  - in C, a character is an integer
  - thus, can do math on characters in C
