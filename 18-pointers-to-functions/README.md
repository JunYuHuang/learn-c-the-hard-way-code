# Exercise 18: Pointers to Functions

## Notes

- pointers to functions
  - i.e. callback functions
  - allows passing a function as a callback to another function
    - i.e. allows HOF (Higher Order Functions)
    - i.e. treat a function (type) as a param of another function
  - making a function pointer:
    - `(*<pointer_name>)(<args...>)`
  - making a type for a function pointer:
    - `typedef (*<fn_name>) (<args...>);`
- misc
  - can treat code as data (see `dump()` function)
  - `destroy()` function
    - overwrites code for `cmp` function with numbers via a pointer
    - most OS's don't protect execution code in memory?
  - big hack in C
    - point a pointer to
      - a function OR
      - a function you write OR
      - a function you write in memory

## Extra Credit

- [ ] ~~1. Get a hex editor and open up `ex18`, and then find the sequence of hex digits that start a function to see if you can find the function in the raw program.~~
  - Skipped
- [ ] ~~2. Find other random things in your hex editor and change them. Rerun your program and see what happens. Strings you find are the easiest things to change.~~
  - Skipped
- [x] 3. Pass in the wrong function for the `compare_cb` and see what the C compiler complains about.
  - See `ec3.c`
  - compiler complains about too many arguments being passed to `cmp` function
- [x] 4. Pass in NULL and watch your program seriously bite it. Then, run the debugger and see what that reports.
  - See `ec4.c`
  - results in segfault
  - debugger says segfault with `0x0000000000000000 in ?? ()` message
- [x] 5. Write another sorting algorithm, then change `test_sorting` so that it takes _both_ an arbitrary sort function and the sort function's callback comparison. Use it to test both of your algorithms.
  - See `ec5.c`
