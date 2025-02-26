# Exercise 43: A Simple Statistics Engine

## Notes

- stats
  - uses for standard deviation and mean:
    1. see if a new sample is interesting OR
    2. collect stats on stats
- most useful stats on stats:
  1. mean of means: stats += a mean sample
  2. mean of standard deviations: stats += a std. dev. sample
- misc
  - neither `stats.h` nor `stats.c` has a function for freeing the allocated memory created with either `Stats_recreate()` or `Stats_create()`
  - `stats.c` is a rolling calculation
  - `static inline` functions are like function-like macros with certain limits
- todos
  - [x] type-copy all this exercise's source code to `./modded`
  - [x] add code comments to `./modded`
  - [x] read text and add notes here
  - [x] watch video and add notes here

## Extra Credit

- [x] 1. Convert the `Stats_stddev` and `Stats_mean` to `static inline` functions in the `stats.h` file instead of in the `stats.c` file.
  - See `./ec-1`
- [ ] ~~2. Use this code to write a performance test of the `string_algos_test.c`. Make it optional, and have it run the base test as a series of samples, and then report the results.~~
  - Skipped
- [ ] ~~3. Write a version of this in another programming language you know. Confirm that this version is correct based on what I have here.~~
  - Skipped
- [ ] ~~4. Write a little program that can take a file full of numbers and spit these statistics out for them.~~
  - Skipped
- [ ] ~~5. Make the program accept a table of data that has headers on one line, then all of the other numbers on lines after it are separated by any number of spaces. Your program should then print out these statistics for each column by the header name.~~
  - Skipped
