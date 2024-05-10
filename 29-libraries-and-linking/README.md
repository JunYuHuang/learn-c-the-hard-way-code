# Exercise 29: Libraries and Linking

## Notes

- C libraries and linking
  - 2 library types in C
    - static libs: like a box of `.o` files
      - like one big `.o` file
      - i.e. C archive library `.a` files
      - good for small-medium sized projects
      - easier set up
    - dynamic libs: OS loads & links them to a C program at runtime
      - many file extensions
        - e.g. C shared object lib `.so` files, `.dll`, etc.
      - like DLL files in Windows
      - good for large projects when have fewer space
  - for dynamic loading of modules e.g. for web servers / apps
- misc
  - `.o` files: C object files
  - can use function pointer typedefs when for linking C files
  - `dlopen()`: like `import` in JavaScript ES6
  - `nm`: Linux tool that lists symbols (e.g. function names) in C object files
  - `-ldl`: `gcc` C compiler flag that links the library `dl`
  - `RTLD_NOW`:
    - an int flag when in calling function `dlopen()`
    - resolves undefined symbols / names before `dlopen()` returns
      - makes `dlopen()` return an error if it can't do that

## Extra Credit

- [x] 1. Were you paying attention to the bad code I have in the `libex29.c` functions? Do you see how, even though I use a `for-loop` they still check for `'\0'` endings? Fix this so that the functions always take a length for the string to work with inside the function.
  - See `./ec-1`
- [x] 2. Take the `c-skeleton` skeleton, and create a new project for this exercise. Put the `libex29.c` file in the `src/` directory. Change the `Makefile` so that it builds this as `build/libex29.so`.
  - See `./ec-2`
- [ ] 3. Take the `ex29.c` file and put it in `tests/ex29_tests.c` so that it runs as a unit test. Make this all work, which means that you'll have to change it so that it loads the `build/libex29.so` file and runs tests similar to what I did manually above.
  - TODO
- [ ] ~~4. Read the `man dlopen` documentation and read about all of the related functions. Try some of the other options to `dlopen` beside `RTLD_NOW`.~~
  - Skipped
