# Exercise 8: If, Else-If, Else

## Notes

- the `main()` function
  - `argc` counts all argument passed to `main()` in `argv`
    - `arg` is a char array
    - count includes the compiled C binary file's name
- C quirks of the `if-statement`
  - a conditional statement is false if it evaluates to 0 else it is true
  - must put parentheses around conditional statements
  - optional to wrap clauses in braces
    - it is bad form if not done

## Extra Credit

- [x] You were briefly introduced to `&&`, which does an _and_ comparison, so go research online the different _Boolean_ operators.
  - `&&`: and
  - `||`: or
  - `!`: not
- [x] Write a few more test cases for this program to see what you can come up with.
  - See `ex8-modded.c`
- [x] Is the first test really saying the right thing? To you, the first argument isn't the same first argument a user entered. Fix it.
  - See `ex8-modded.c`
