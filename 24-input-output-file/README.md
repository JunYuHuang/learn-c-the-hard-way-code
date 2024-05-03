# Exercise 24: Input, Output, Files

## Notes

- common `f` (file) functions (14+)
  - inconsistent
  - use `fgets()` over `gets()`
  - `gets()` is broken and should never be used
    - why?
      - no limit on how long the input string is
      - may overwrite other parts of the program in memory
  - `scanf` function family is inverse of `printf` function family
- fuzzing: input random garbage to a program
- misc
  - `&<variable_name>`: a pointer AND a memory address
  - can replace `stdin` with `fopen()` in the code
  - `fscanf()` vs `fgets()`?
    - `fscanf()`:
      - reads up to whitespace and does NOT store it
    - `fgets()`:
      - reads up to a newline and stores it
  - `scanf()` vs `fscanf()`?
    - `scanf()`: is like `fscanf()` with `stdin` as its 1st arg
    - `fscanf()`: can set file input stream e.g. `stdin` or something else
- look up:
  - `fscanf()`: TODO
  - `scanf()`: TODO
  - `fgets()`: TODO
  - `gets()`: TODO
  - `fopen()`: TODO
  - `freopen()`: TODO
  - `fdopen()`: TODO
  - `fclose()`: TODO
  - `fcloseall()`: TODO
  - `fgetpos()`: TODO
  - `fseek()`: TODO
  - `ftell()`: TODO
  - `rewind()`: TODO
  - `fprintf()`: TODO
  - `fwrite()`: TODO
  - `fread()`: TODO

## Extra Credit

- [x] Rewrite this to not use `fscanf` at all. You'll need to use functions like `atoi` to convert the input strings to numbers.
  - See `./ec-1`
- [x] Change this to use plain `scanf` instead of `fscanf` to see what the difference is.
  - See `./ec-2`
- [x] Fix it so that their input names get stripped of the trailing newline characters and any whitespace.
  - See `./ec-3`
- [ ] ~~Use `scanf` to write a function that reads one character at a time and fills in the names but doesn't go past the end. Make this function generic so it can take a size for the string, but just make sure you end the string with `'\0'` no matter what.~~
  - Skipped
