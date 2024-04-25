# Exercise 41: Writing and Using Functions

## Notes

- forward declaration
  - like buying a good with credit and paying it off later
  - defines a function's type and signature
  - allows defining functions in any order
  - why?
    - header files are full of them
    - avoids the "deadly embrace"
      - deadly embrace = circular or mutual refs
        - e.g. 2 functions that call each other in their bodies
- convention to define `main()` at end of C source file
- "conflicting type" compile error
  - means wrong type passed or no function declaration
- good to set forward declarations at top of file

## Extra Credit

- [x] Rework these functions so that you have fewer functions. For example, do you really need `can_print_it`?
  - No
  - See `ex14_modded.c`
- [x] Have `print_arguments` figure out how long each argument string is by using the `strlen` function, and then pass that length to `print_letters`. Then, rewrite `print_letters` so it only processes this fixed length and doesn't rely on the `'\0'` terminator. You'll need the `#include <string.h>` for this.
  - See `ex14_modded.c`
- [x] Use `man` to look up information on `isalpha` and `isblank`. Use other similar functions to print out only digits or other characters.
  - similar functions: `isalnum()`, `isdigit()`, etc.
- [ ] ~~Go read about how other people like to format their functions. Never use the _K&R syntax_ (it's antiquated and confusing) but understand what it's doing in case you run into someone who likes it.~~
  - Skipped
