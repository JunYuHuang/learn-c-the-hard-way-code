# Exercise 21: Advanced Data Types and Flow Control

## Notes

- mostly review
- data types (6):
  - `int`: stores an int that defaults to 32-bit in size (4 bytes)
  - `double`: stores a large decimal (8 bytes)
  - `float`: stores a smaller decimal (4 bytes)
  - `char`: holds a char (1 byte)
  - `void`: no type like NULL (1 byte)
  - `enum`: named int constant (4 bytes)
- type modifiers (4):
  - `unsigned`: non-negative numbers + 0 only
  - `signed`: both negative + positive numbers + 0
  - `long`: bigger number via more space (e.g. double size)
  - `short`: smaller numbers via less space (e.g. half size)
- type qualifiers (3):
  - see `ex21.c`
- type conversion:
  - promotes smaller (sized?) side to match larger side
  - order / priority (5):
    1. `long double`
    2. `double`
    3. `float`
    4. `int` (only `char` and `short int`)
    5. `long`
  - override order with explicit type casts
  - always promote UP, not down
- type sizes
  - see `ex21.c`
  - for getting exact sized int types
  - 8 types of pattern `(u)int(BITS)_t`
  - many macros e.g.
    - `INT(N)_MAX`
    - `INT(N)_MIN`
    - `UINT(N)_MAX`
- operators
  - 5 forms:
    - binary
    - unary: op on its own e.g. `-x`
    - prefix: op before var e.g. `--x`
    - postfix
    - ternary
  - math ops (11)
    - `()`: call function
  - data ops (6)
    - `->`: struct pointer access
    - `.`: struct value access
    - `sieof`: size of a type or var
    - `&` (unary): memory address of
    - `*` (unary): value of
  - logic ops (6)
  - bit(wise) ops (6): for modding raw bits in ints
    - `&` (binary): AND
    - `<<`: shift left
    - `>>`: shift right
    - `^`: XOR
    - `|`: OR
    - `~`: compliment (flips all bits)
  - boolean ops (4)
    - `?:`: ternary truth test
  - assign ops (11)
  - control structs (4)
    - `do-while`
    - `break`
    - `continue`
    - `goto`: like `catch` part of a `try-catch` clause that goes to `error:` label of a function?

## Extra Credit

- [ ] ~~Read `stdint.h` or a description of it, and write out all the available size identifiers.~~
  - Skipped
  - See https://en.cppreference.com/w/c/types/integer
- [ ] ~~Go through each item here and write out what it does in code. Research it online so you know you got it right.~~
  - Skipped
- [ ] ~~Get this information memorized by making flash cards and spending 15 minutes a day practicing it.~~
  - Skipped
- [ ] ~~Create a program that prints out examples of each type, and confirm that your research is right.~~
  - Skipped
