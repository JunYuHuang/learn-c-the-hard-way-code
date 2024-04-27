# Exercise 15: Pointers, Dreaded Pointers

## Notes

- pointers
  - like a key of a key-value pair in a hashmap
  - like a secret shortcut to a place (a memory address)
  - like a data type of an array + an int index
  - is the memory address of another variable's value
    - address is a big integer
    - address can be in hexadecimal format
  - why?
    - fast / direct access to a value
    - manually index data into memory blocks when an array can't
  - array subscript syntax (i.e. index access) uses pointers under the hood
  - void pointers point to any or an unknown type
- pointer uses cases (4):
  - get a memory chunk and a pointer from the OS
  - pass big memory blocks to functions
  - use a function as a callback via its address
  - misc (3):
    - read complex memory chunks
    - read network socket bytes into data structures
    - parse / read files
- pointer lexicon (syntax):
  - `type *ptr`: makes a pointer `ptr` of type `type`
  - `*ptr`: gets the value of what the pointer `ptr` points to
    - i.e. "dereferences" the pointer
  - `*(ptr + i)`: gets the value of what `ptr` plus `i` points to
  - `&thing`: gets the (memory) address of `thing`
    - reverse of `*ptr`
  - `type *ptr = &thing`: make a pointer `ptr` of type `type` set to the (memory) address of `thing`
  - `ptr++`: increment where the pointer `ptr` points to
- misc
  - program is like a big array
  - mostly treat arrays and pointers the same
    - but they are NOT THE SAME
  - C strings are pointers to char arrays
  - best to use array syntax for accessing pointer (values)
  - bad to type cast between pointers of unlike types

## Extra Credit

- [x] Rewrite all of the arrays in this program as pointers.
  - See `ex15_modded.c`
- [x] Rewrite all of the pointers as arrays.
  - See `ex15_modded.c`
- [ ] ~~Go back to some of the other programs that use arrays and try to use pointers instead.~~
  - Skipped
- [x] Process command line arguments using just pointers similar to how you did `names` in this one.
  - See `ex15_modded.c`
- [ ] ~~Play with combinations of getting the value of and the address of things.~~
  - Skipped
- [x] Add another `for-loop` at the end that prints out the addresses that these pointers are using. You'll need the `%p` format for printf.
  - See `ex15_modded.c`
- [x] Rewrite this program to use a function for each of the ways you're printing out things. Try to pass pointers to these functions so that they work on the data. Remember you can declare a function to accept a pointer, but just use it like an array.
  - See `ex15_modded.c`
- [x] Change the `for-loops` to `while-loops` and see what works better for which kind of pointer usage.
  - See `ex15_modded.c`
