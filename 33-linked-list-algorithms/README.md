# Exercise 33: Linked List Algorithms

## Notes

- sorting algorithms
  - bubble sort
    - very slow
  - merge sort
    - decent
  - quick sort
    - used often in real world
- how to code review
  - check every line of code
    - check if each function call is being called correctly
      - proper arg value(s)
      - proper return value(s)
      - etc.
- misc
  - bug with "undefined reference" or "multiple definition of" issue when importing headers or C files
    - fix:
      - replace `Makefile` with updated one from the [`liblcthw` GitHub repo](https://github.com/zedshaw/liblcthw/blob/master/Makefile)
      - remove `-lbsd` in line 15 of the `Makefile`
  - `inline` keyword in C:
    - makes a function faster?
    - a C program / compiler performance optimization?
  - real world stats / profiling > theoretical (i.e. Big O) perf
  - learn tag jumping in `vim` for doing code review
  - learn exuberant ctags
    - use to create and load tags in `vim`
  - many sort algorithms suffer when input list is already sorted

## My Solution Notes

- bubble sort
  - edge cases to handle
    - empty list
    - list of size 1
    - list of size > 1
  - double nested loop
    - outer `do-while-loop`
      - loop while `is_swapped` bool int is true
    - inner loop
      - use `LIST_FOREACH` function macro
      - if 2 adjacent elements are out of order,
        - swap their values
  - how to know if 2 elements `list[i]` and `list[i + 1]` in the list are out of order given a compare callback function?
    - compare callback function returns an int that means `list[i]` comes AFTER `list[i + 1]` when `list[i]` is supposed to come before `list[i + 1]`
  - how to swap 2 adjacent nodes in C?
    - only swap their values using a third temp `void` pointer that temporarily stores the value of either `list[i]` or `list[i + 1]`
- merge sort (recursive top-down approach)
  - see https://en.wikipedia.org/wiki/Merge_sort
  - functions
    - `merge_sort()`
    - `merge()`

## How To Improve It

- [ ] ~~1. The merge sort does a crazy amount of copying and creating lists, so find ways to reduce this.~~
  - Skipped
- [ ] ~~2. The bubble sort description in Wikipedia mentions a few optimizations. Try to implement them.~~
  - Skipped
- [ ] ~~3. Can you use the `List_split` and `List_join` (if you implemented them) to improve merge sort?~~
  - Skipped
- [ ] ~~4. Go through of all the defensive programming checks and improve the robustness of this implementation, protecting against bad `NULL` pointers, and then create an optional debug level invariant that works like `is_sorted` does after a sort.~~
  - Skipped

## Extra Credit

- [ ] ~~1. Create a unit test that compares the performance of the two algorithms. You'll want to look at `man 3 time` for a basic timer function, and run enough iterations to at least have a few seconds of samples.~~
  - Skipped
- [ ] ~~2. Play with the amount of data in the lists that need to be sorted and see if that changes your timing.~~
  - Skipped
- [ ] ~~3. Find a way to simulate filling different sized random lists, measuring how long they take. Then, graph the result to see how it compares to the description of the algorithm.~~
  - Skipped
- [x] 4. Try to explain why sorting linked lists is a really bad idea.
  - It's very slow because traversing linked lists is slow
  - Slow to traverse a linked list because must start from its first or last node
- [ ] ~~5. Implement a `List_insert_sorted` that will take a given value, and using the `List_compare`, insert the element at the right position so that the list is always sorted. How does using this method compare to sorting a list after you've built it?~~
  - Skipped
- [ ] ~~6. Try implementing the bottom-up merge sort described on the Wikipedia page. The code there is already C, so it should be easy to recreate, but try to understand how it's working compared to the slower one I have here.~~
  - Skipped
