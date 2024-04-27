# Exercise 16: Struts And Pointers To Them

## Notes

- structs
  - like precursor to objects
  - like a ragged array
- more pointer lexicon
  - `ptr->elem`: gets the value of the `elem` member of the struct that the pointer `ptr` points to
- misc
  - `malloc()`: memory allocator function
    - gets a pointer to a memory chunk for some data (e.g. a struct)
    - makes the memory chunk on the heap
  - `free()`: frees up unused memory chunks (e.g. structs)
    - calling it on a thing does not make the thing `NULL`
  - `struct.elem` vs `ptr_struct->elem` syntax
    - both get the value of `elem`
    - `elem` is a member of the struct `struct`
    - first syntax is for struct variables
    - second syntax is for a pointer to the struct
    - second syntax is syntatic sugar for the first
      - e.g. `ptr_struct->elem` is the same as `(*ptr_struct).elem`
  - `assert()`: stops program if it returns false
    - like if-statement guard clause
  - dereferencing `NULL` crashes the program
    - cannot access `NULL`'s contents because `NULL` is empty
  - normal variables, functions, etc. are set on the stack

## Extra Credit

- [x] How to create a `struct` on the _stack_ just like you're making any other variable.
  - See `ex16_modded.c`
- [x] How to initialize it using the `x.y` (period) character instead of the `x->y `syntax.
  - See `ex16_modded.c`
- [x] How to pass a structure to other functions without using a pointer.
  - See `ex16_modded.c`
