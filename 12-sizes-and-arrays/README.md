# Exercise 12: Sizes and Arrays

## Notes

- `sizeof()`:
  - function that gets bytes needed to store a type or variable value
  - gets diff value if called with a pointer
- arrays in C
  - are a continuous block of memory cut in pieces
  - fills empty spots with 0's (null bytes)
  - strings (i.e. char arrays) always end with a null byte (`'\0'`)
    - null byte takes an extra slot in the string
- treats strings and byte arrays the same
- 2 ways to make strings:
  - with double quotes (`"abc"`) syntax OR
  - with array syntax (`{ 'a', 'b', 'c', '\0' }`)

## Extra Credit

- [x] Try assigning to elements in the `areas` array with `areas[0] = 100;` and similar.
  - See `ex12_modded/c`
- [x] Try assigning to elements of `name` and `full_name`.
  - See `ex12_modded/c`
- [x] Try setting one element of `areas` to a character from `name`.
  - See `ex12_modded/c`
- [x] Search online for the different sizes used for integers on different CPUs.
  - depends on compiler, CPU, and OS - e.g. 32-bit CPU, 64-bit CPU
  - see https://stackoverflow.com/questions/7180196/size-of-integer-in-c
