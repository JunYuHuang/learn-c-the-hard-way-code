# Exercise 29: Libraries and Linking

## Notes

- TODO

## Extra Credit

- [ ] 1. Were you paying attention to the bad code I have in the `libex29.c` functions? Do you see how, even though I use a `for-loop` they still check for `'\0'` endings? Fix this so that the functions always take a length for the string to work with inside the function.
  - TODO
- [ ] 2. Take the `c-skeleton` skeleton, and create a new project for this exercise. Put the `libex29.c` file in the `src/` directory. Change the `Makefile` so that it builds this as `build/libex29.so`.
  - TODO
- [ ] 3. Take the `ex29.c` file and put it in `tests/ex29_tests.c` so that it runs as a unit test. Make this all work, which means that you'll have to change it so that it loads the `build/libex29.so` file and runs tests similar to what I did manually above.
  - TODO
- [ ] 4. Read the `man dlopen` documentation and read about all of the related functions. Try some of the other options to `dlopen` beside `RTLD_NOW`.
  - TODO
