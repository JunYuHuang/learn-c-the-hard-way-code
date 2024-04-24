# Exercise 10: Switch Statements

## Notes

- switch statement
  - is a jump table
    - can only use expressions that result in integers
  - like a mini parser
  - like a controlled GOTO based on an integer
  - like an if statement with labels and numbers
  - case statements only work with constants in C
- good practices
  - always add a `default` branch
  - don't allow fall through unless needed
  - always write `case` and `break` before writing its handler code
  - prefer `if-statement`s over `switch-statement`s
- extra credit notes
  - there are `toupper()` and `tolower()` functions
- return a non-zero value to tell the OS that the program erred
- comma operator workings for `(expression1, expresion1)`
  - runs `expression1`
  - runs `expression2`
  - returns value of `expression2`

## Extra Credit

- [x] Write another program that uses math on the letter to convert it to lowercase, and then remove all of the extraneous uppercase letters in the switch.
  - See `ex10-modded.c`
- [x] Use the `','` (comma) to initialize `letter` in the `for-loop`.
  - See `ex10-modded.c`
- [x] Make it handle all the arguments you pass it with yet another `for-loop`.
  - See `ex10-modded.c`
- [x] Convert this `switch-statement` to an `if-statement`. Which do you like better?
  - Prefer `if-statement`
  - See `ex10-modded.c`
- [x] In the case for `'Y'` I have the break outside of the `if-statement`. What's the impact of this, and what happens if you move it inside of the `if-statement`. Prove to yourself that you're right.
  - The case for handling a non-vowel `Y` character in a string will fall thru to the `default` case. Then, the `default` case prints that the `Y` character is not a vowel.
  - See `ex10-modded.c`
