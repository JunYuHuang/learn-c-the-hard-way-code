# Exercise 39: String Algorithms

## Notes

- formal code review process / steps
  1. start at a changed code part's entry point
  2. verify each function's calling params are right
  3. enter & verify each function's body code is right (line-by-line)
  4. repeat up to step 2 for each function
  5. confirm return values and their usage when exiting functions
  6. confirm any missed calls to changed functions
- code review key points
  - check pointer derefs & defend against `NULL`
  - check `if-statments` and `while-loops` for exiting
  - check if return values will be valid
  - check if allocated memory and other resources are freed
  - confirm all system call params are right via `man` pages
- consider recording your own code review
  - what if I tracked and studied my code reviews?
  - code review: like watching yourself code as a neutral 3rd party
  - many compile errors: means I'm not doing well
  - untested code
- misc
  - `ssize_t`: `size_t` data but signed; i.e. allows negative ints
  - Boyer-Moore-Horspool (BMH) algorithm: a string search algorithm
  - study / analyse stuff

## Extra Credit

- [ ] ~~1. See if you can make the `Scan_find` faster. Why is my implementation here slow?~~
  - Skipped
- [ ] ~~2. Try some different scan times and see if you get different numbers. What impact does the length of time that you run the test have on the `scan` times? What can you say about that result?~~
  - Skipped
- [ ] ~~3. Alter the unit test so that it runs each function for a short burst in the beginning to clear out any warm up period, and then start the timing portion. Does that change the dependence on the length of time the test runs? Does it change how many operations per second are possible?~~
  - Skipped
- [ ] ~~4. Make the unit test randomize the strings to find and then measure the performance you get. One way to do this is to use the `bsplit` function from `bstrlib.h` to split the `IN_STR` on spaces. Then, you can use the `bstrList` struct that you get to access each string it returns. This will also teach you how to use `bstrList` operations for string processing.~~
  - Skipped
- [ ] ~~5. Try some runs with the tests in different orders to see if you get different results.~~
  - Skipped
