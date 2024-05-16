# Exercise 35: Sorting and Searching

## Notes

- TODO
- misc
  - TODO: get copy and pasted code working
    - bug: `darray_algos_tests.c:54: undefined reference to 'DArray_qsort'`

## How To Improve It

- [ ] 1. Use a binary search to find the minimum position for the new element, then only sort from there to the end. You find the minimum, put the new element on the end, and then just sort from the minimum on. This will cut your sort space down considerably most of the time.
  - TODO
- [ ] 2. Keep track of the biggest key currently being used, and then only sort enough digits to handle that key. You can also keep track of the smallest number, and then only sort the digits necessary for the range. To do this, you'll have to start caring about CPU integer ordering (endianness).
  - TODO

## Extra Credit

- [ ] 1. Implement quicksort, heapsort, and merge sort and then provide a `#define` that lets you pick between the two, or create a second set of functions you can call. Use the technique I taught you to read the Wikipedia page for the algorithm, and then implement it with the psuedo-code.
  - TODO
- [ ] 3. Compare the performance of your optimizations to the original implementations.
  - TODO
- [ ] 2. Use these sorting functions to create a `DArray_sort_add` that adds elements to the `DArray` but sorts the array after.
  - TODO
- [ ] 3. Write a `DArray_find` that uses the binary search algorithm from `RadixMap_find` and the `DArray_compare` to find elements in a sorted `DArray`.
  - TODO
