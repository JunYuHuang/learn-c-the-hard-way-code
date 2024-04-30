# Exercise 17: Heap and Stack Memory Allocation

## Notes

- heap vs stack
  - for most cases,
    - if some variable / data uses `malloc()` -> it is in the heap
    - else, it is on the stack
  - heap:
    - pointers point to stuff in heap
    - use `malloc()` and `free()` to manage memory chunks of data in the heap
    - failing to `free()` memory chunks leaks memory (bad)
  - stack:
    - stores temp variables in functions
    - vars are pushed when set and popped when their function exits
    - don't need to manually manage memory
  - both:
    - places to store memory chunks
- common heap and stack issues (3):
  - dangling pointer (via de-allocation):
    - pointers to `malloc()`'d memory chunks get lost when the function that has the pointer exits
  - stack overflow:
    - too much data on the stack stops the program
    - fix: use the heap with `malloc()`
  - dangling pointer (via function call):
    - segfaults from passing to or returning stack-pointed pointers from a function
    - why? pointed-to data is popped off from the stack
- call-by-value vs call-by-ref
  - call-by-ref uses pointers and less memory (in heap?)
  - call-by-value copies thing into stack memory
- imported headers and their macros / functions:
  - `stdio.h`:
    - `FILE`: type for handling a file (stream)
    - `fclose()`: closes a file
    - `fflush()`: saves unchanged changes to a file
    - `fopen()`: opens a file
    - `fread()`: reads an `x` part of a file
    - `fwrite()`: adds unsaved changes to a file (in-memory only)
    - `perror()`: writes an error message to standard error
    - `rewind()`: moves the file position cursor / index / pointer to the start of a file (stream)
  - `assert.h`:
    - `assert()`: stops the program if called with a false-resulting expression, else it does nothing
  - `stdlib.h`:
    - `atoi()`: ASCII TO Integer; converts a char to an int
    - `exit()`: stops the program early
    - `free()`
    - `malloc()`
  - `errno.h`:
    - `errno`: error number (integer) macro; program is OK if it is 0, else it is not (some positive integer)
  - `string.h`:
    - `memset()` ?
    - `strncpy()`: copies a string with funky UB (Undefined Behavior)
      - if source string size < destination string size,
        - overwrites remaining destination string bytes with null bytes (`'\0'`)
- misc
  - `set` is a boolean flag in `Address`
  - CPP = C Pre-Processor; for making constants and macros
  - in C, most macros are in ALL_CAPS but some are in lowercase
  - OS cleans up resources when a program exits
- standard (I/O) stream:

  - like virtual pipes that programs use to send and get data

  ```
                          +-> std. output
  std. input -> program --+
                          +-> std. error
  ```

## Breaking It

- [x] 1. The classic way is to remove some of the safety checks so that you can pass in arbitrary data. For example, remove the check on line 160 that prevents you from passing in any record number.
  - Results in a segfault.
  - See `ex17_m.c`
- [x] 2. You can also try corrupting the data file. Open it in any editor and change random bytes, and then close it.
  - Fails to load database.
  - See `ex17_m.c`
- [ ] ~~3. You could also find ways to pass bad arguments to the program when it's run. For example, getting the file and action backwards will make it create a file named after the action, and then do an action based on the first character.~~
  - Skipped
- [x] 4. There's a bug in this program because `strncpy` is poorly designed. Go read about `strncpy` and try to find out what happens when the `name` or `address` you give is greater than 512 bytes. Fix this by simply forcing the last character to `'\0'` so that it's always set no matter what (which is what `strncpy` should do).
  - Bug causes the `name` or `address` to overwrite its `Address` or adjacent `Address`es in the file
  - My fix: set `addr->name`'s last char to a null byte `'\0'`
  - See `ex17_m.c`
- [ ] ~~5. In the extra credit, I have you augment the program to create arbitrary size databases. Try to see what the biggest database is before you cause the program to die due to lack of memory from `malloc`.~~
  - Skipped

## Extra Credit

- [x] 1. The `die` function needs to be augmented to let you pass the `conn` variable, so it can close it and clean up.
  - See `ec1.c`
- [ ] 2. Change the code to accept parameters for `MAX_DATA` and `MAX_ROWS`, store them in the `Database` struct, and write that to the file, thus creating a database that can be arbitrarily sized.
  - See `ec2.c`
- [ ] 3. Add more operations you can do with the database, like `find`.
  - TODO
- [ ] 4. Read about how C does it's struct packing, and then try to see why your file is the size it is. See if you can calculate a new size after adding more fields.
  - TODO
- [ ] 5. Add some more fields to `Address` and make them searchable.
  - TODO
- [ ] 6. Write a shell script that will do your testing automatically for you by running commands in the right order. Hint: Use `set -e` at the top of a `bash` to make it abort the whole script if any command has an error.
  - TODO
- [ ] 7. ~~Try reworking the program to use a single global for the database connection. How does this new version of the program compare to the other one?~~
  - Skipped
- [ ] 8. ~~Go research stack data structure and write one in your favorite language, then try to do it in C.~~
  - Skipped
