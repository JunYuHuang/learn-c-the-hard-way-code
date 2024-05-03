# Exercise 22: The Stack, Scope, and Globals

## Notes

- overview of files
  - `ex22.h`: header file that sets up external vars and functions
  - `ex22.c`: source file that will become an object file `ex22.o` with functions and variables defined from `ex22.h`
  - `ex22_main.c`: real `main` that includes the other 2 files
- rules for avoiding (stack-related) bugs (5):
  - do NOT shadow variables (use same var name in unlike scopes)
  - reduce global variable use
  - put on heap if unsure
    - i.e. use `malloc()`, `free()`, and pointers
  - don't use function static variables
  - no reusing function parameters
- misc
  - `extern` keyword:
    - like `public` access modifier
    - like exporting a variable to other C files
  - `static` (file level):
    - like `private` access modifier
    - makes variable only usable in the .c file it is declared in
  - `.o` files: object files for access by C linker
  - refactor global state into a struct with getters and settesr
    - makes it thread safe

## How To Break It

- [ ] ~~1. Try to directly access variables in `ex22.c` from `ex22_main.c` that you think you can't. For example, can you get at ratio inside `update_ratio`? What if you had a pointer to it?~~
  - Dropped (WIP)
  - See `./htbi-1`
- [x] 2. Ditch the `extern` declaration in `ex22.h` to see what errors or warnings you get.
  - See `./htbi-2`
  - No issues with `cc` compiler
- [ ] ~~3. Add `static` or `const` specifiers to different variables, and then try to change them.~~
  - Skipped

## Extra Credit

- [x] 1. Research the concept of pass by value versus pass by reference. Write an example of both.
  - TLDR: pointer -> ref, else -> value
  - pass-by-value:
    - call a function with a copy of a variable
    - updating this var (copy) does NOT affect the original var
    - e.g. passing a non-pointer variable to a function call
  - pass-by-ref:
    - call a function with the original variable
    - updating this var DOES affects the original var
    - e.g. passing a pointer to a function call
- [ ] ~~2. Use pointers to gain access to things you shouldn't have access to.~~
  - Skipped
- [ ] ~~3. Use your debugger to see what this kind of access looks like when you do it wrong.~~
  - Skipped
- [x] 4. Write a recursive function that causes a stack overflow. Don't know what a recursive function is? Try calling `scope_demo` at the bottom of `scope_demo` itself so that it loops.
  - See `./ex-4`
- [x] 5. Rewrite the `Makefile` so that it can build this.
  - See `./ex-5`
