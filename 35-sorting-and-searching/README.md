# Exercise 35: Sorting and Searching

## Notes

- radix sort: a weird sorting algorithm for educational value
  - only good for
    - 1 map of int set to another
    - 1 map of int set to a pointer
  - `RMElement`: RadixMap Element; i.e. a key-value pair
  - `RadixMap_find()`: uses binary search
- separate asserts / checks from load / set-up code in functions
- misc
  - get copy and pasted code working (fixed now)
    - problem:
      - `stdlib.h` excludes functions `heapsort()` and `quicksort()`
      - `list_algos_tests.c` fails due to `undefined reference to 'heapsort'`
    - fix
      - update `Makefile` to link to the `libbsd-dev` library
      - see https://github.com/zedshaw/liblcthw/pull/22
      - install `libbsd-dev` package on my WSL Ubuntu
      - update `Makefile` to match https://github.com/zedshaw/liblcthw/blob/master/Makefile

## How To Improve It

- [ ] ~~1. Use a binary search to find the minimum position for the new element, then only sort from there to the end. You find the minimum, put the new element on the end, and then just sort from the minimum on. This will cut your sort space down considerably most of the time.~~
  - Skipped
- [ ] ~~2. Keep track of the biggest key currently being used, and then only sort enough digits to handle that key. You can also keep track of the smallest number, and then only sort the digits necessary for the range. To do this, you'll have to start caring about CPU integer ordering (endianness).~~
  - Skipped

## Extra Credit

- [ ] ~~1. Implement quicksort, heapsort, and merge sort and then provide a `#define` that lets you pick between the two, or create a second set of functions you can call. Use the technique I taught you to read the Wikipedia page for the algorithm, and then implement it with the psuedo-code.~~
  - Skipped
- [ ] ~~3. Compare the performance of your optimizations to the original implementations.~~
  - Skipped
- [ ] ~~2. Use these sorting functions to create a `DArray_sort_add` that adds elements to the `DArray` but sorts the array after.~~
  - Skipped
- [ ] ~~3. Write a `DArray_find` that uses the binary search algorithm from `RadixMap_find` and the `DArray_compare` to find elements in a sorted `DArray`.~~
  - Skipped
