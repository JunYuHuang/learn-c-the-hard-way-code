# Exercise 39: String Algorithms

## Notes

- a
- TODOs
  - [x] get copy and pasted code compiling
  - [ ] type-copy the source code into `./modded`
  - [ ] add comments to the code in `./modded`

## Extra Credit

- [ ] 1. See if you can make the `Scan_find` faster. Why is my implementation here slow?
  - TODO
- [ ] 2. Try some different scan times and see if you get different numbers. What impact does the length of time that you run the test have on the `scan` times? What can you say about that result?
  - TODO
- [ ] 3. Alter the unit test so that it runs each function for a short burst in the beginning to clear out any warm up period, and then start the timing portion. Does that change the dependence on the length of time the test runs? Does it change how many operations per second are possible?
  - TODO
- [ ] 4. Make the unit test randomize the strings to find and then measure the performance you get. One way to do this is to use the `bsplit` function from `bstrlib.h` to split the `IN_STR` on spaces. Then, you can use the `bstrList` struct that you get to access each string it returns. This will also teach you how to use `bstrList` operations for string processing.
  - TODO
- [ ] 5. Try some runs with the tests in different orders to see if you get different results.
  - TODO
