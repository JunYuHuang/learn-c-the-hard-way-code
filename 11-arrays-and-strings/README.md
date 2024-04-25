# Exercise 11: Arrays and Strings

## Notes

- can make strings as
  - char array OR
  - char pointer (better way)
- C strings are broken
  - must end with a null byte (the `'\0'` char) in C
  - null byte terminator causes many issues
  - causes many bugs
  - designed to save memory originally when memory was scarce
- C treats a string and a char array the same
- extra credit
  - for the 4th task:
    - check out `memcpy`

## Extra Credit

- [x] Assign the characters into `numbers`, and then use `printf` to print them one character at a time. What kind of compiler warnings do you get?
  - See `ex11-modded.c`
  - no compiler warnings from `cc` C compiler
  - prints numbers
- [x] Do the inverse for `name`, trying to treat it like an array of `int` and print it out one `int` at a time. What does the debugger think of that?
  - See `ex11-modded.c`
  - `No such file or directory` message from `gdb` debugger when stepping thru `main()`
  - `name` prints out nothing
- [x] In how many other ways can you print this out?
  - several depending on what format / conversion specifier is used
  - see the [C/C++ reference docs](https://en.cppreference.com/w/c/io/fprintf)
- [ ] ~~If an array of characters is 4 bytes long, and an integer is 4 bytes long, then can you treat the whole `name` array like it's just an integer? How might you accomplish this crazy hack?~~
  - Skipped
- [ ] ~~Take out a piece of paper and draw each of these arrays as a row of boxes. Then do the operations you just did on paper to see if you get them right.~~
  - Skipped
- [x] Convert `name` to be in the style of `another` and see if the code keeps working.
  - See `ex11-modded.c`
  - Code works until it tries to update the individual char values in `name` using the array index syntax.
  - The failed attempt crashes the program resulting in a segmentation fault.
