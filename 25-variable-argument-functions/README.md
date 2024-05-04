# Exercise 25: Variable Argument Functions

## Notes

- variadic / variable arguments:
  - like rest arguments in JavaScript
- misc
  - general rule:
    - prob have a bug if working with a string without its length
  - macro functions are a way to write functions that take in generic types?
  - pointer vs array: similar with following diffs:
    - pointer
      - stores another variable's (memory) address
      - `sizeof(PTR)` gets memory used by pointer variable
      - `&PTR` gets pointer's address
      - `char *PTR = "abc"` sets pointer to `"abc"` string's address
      - CAN set a value to pointer variable
      - CAN do arithmetic on pointer variable e.g. `PTR++`
    - array
      - ordered group of the same data types
      - `sizeof(ARR)` gets memory used by all elements in array
      - `ARR` = `&ARR[0]`
      - `char array[] = "abc"` sets 1st 4 elements in array to `'a'`, ... `'\0'`
      - can NOT set a value to array variable
      - can NOT do arithmetic on array variable
- look up:
  - `va_list`: stack / array typedef for holding variable arguments
  - `va_start()`: allows access to variable arguments
  - `va_end()`: stops access to variable arguments
  - `va_arg()`: gets the next variable argument in the `va_list`
  - `calloc()`: `malloc()` but sets memory given to all zeroes
  - `feof()`: checks if reached the end of the file (stream)
  - `ferror()`: checks if there are error(s) in the file (stream)
  - `fgetc()`: gets the next char in the file (stream) as an int
  - `stdin`: standard input stream macro (FILE?)
  - ~~`strtol()`: converts a string to a long int~~

## Extra Credit

- [x] Make double and triple sure that you know what each of the `out_` variables are doing. Most importantly, you should know what is `out_string` is and how it's a pointer to a pointer, so that you understand when you're setting the pointer versus the contents is important.
  - See `./ec-1`
- [ ] Write a similar function to `printf` that uses the varargs system, and rewrite `main` to use it.
  - See `./ec-2`
- [x] As usual, read the man page on all of this so that you know what it does on your platform. Some platforms will use macros, others will use functions, and some will have these do nothing. It all depends on the compiler and the platform you use.
  - See [Notes](#notes)
