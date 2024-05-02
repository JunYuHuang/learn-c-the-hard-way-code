# Exercise 19: Zed's Awesome Debug Macros

## Notes

- macros
- misc
  - `goto` is like the `catch` in a `try-catch` block
  - `#ifndef <var>`: if `<var>` is not defined
  - `#__VAR_ARGS__`: variadic argument macro
  - good to set `errno` to 0 if OK?
  - good to always uses braces for conditional statements / blocks
  - `make CPPFLAGS=-DNDEBUG ex19`: way to set macro flags in CLI

## Extra Credit

- [x] Put `#define NDEBUG` at the top of the file and check that all of the debug messages go away.
  - See `ex19_m.c`
- [x] Undo that line, and add `-DNDEBUG` to `CFLAGS` at the top of the `Makefile`, and then recompile to see the same thing.
  - See `ex19_m.c` and `Makefile`
- [x] Modify the logging so that it includes the function name, as well as the `file:line`.
  - Search for `gcc __file__` online
    - note `__file__` and `__func__`
  - See `ec3.c` and `dbg_ec3.h`
