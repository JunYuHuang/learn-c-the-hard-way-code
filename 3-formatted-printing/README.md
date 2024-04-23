# Exercise 3: Formatted Printing

```bash
# build the binary
make ex3

# run the binary
./ex3

# delete the binary
make clean
```

## Notes

- always initialize variables

## External Research

- all `printf` escape codes (e.g. `\n`) and format sequences (e.g. `%s`)
  - see the docs
    - [C / C++ docs](https://en.cppreference.com/w/c/io/fprintf)
    - [C escape codes](https://en.wikipedia.org/wiki/Escape_sequences_in_C)
    - [C format specifiers](https://www.geeksforgeeks.org/format-specifiers-in-c/)
  - escape codes
    - `\b`: backspace
    - `\e`: escape char
  - format sequences: for printing variables to standard output
    - `%%`: literal `%`
    - `%c`: 1 char
    - `%s`: string (pointer to char array)
    - `%d` or `%i`: signed integer as decimal
    - `%o`: unsigned integer as octal rep
