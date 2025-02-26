# Exercise 27: Creative and Defensive Programming

## Notes

- normally, program creatively then defensively
- defensive programming:
  - assume mistakes and try to prevent them
  - I am not my code
- defensive programming strategies (8+):
  - never trust input
    - function good practices (7)
      - mark preconditions for params
      - add `assert` calls
      - return error code for other preconditions
      - document why for preconditions
      - ensure inputs are OK or stop if updating inputs
      - check function return (error) codes
      - return consistent error codes
  - prevent errors
    - step-by-step process (6)
  - fail early and openly
    - handling errors in C (2):
      - return error code OR
      - stop the process
    - avoid stopping / aborting when writing libraries
    - e.g. using asserts / test function macros
  - document assumptions / beliefs
    - like writing contracts with invariants and postconditions
    - invariant: condition that must be true in a function
    - postcondition: guarantee on a function's exit value or result
    - e.g. comment on expectations in code, add `assert()` callss
  - prevent > docs
    - e.g. poor design of `glob()` function
  - automate everything
    - e.g. write a `Makefile` that runs tests for a C program
    - common things to automate (5)
      - tests
      - build
      - deploy
      - sys admin
      - error reporting
  - simplify and clarify
    - simple != can understand
    - simple: make smaller with less parts or action
    - tests for judging which function is better (5)
      - no errors
      - the working one
      - makes expected result
      - has less stuff
      - simple + dirty > complex + clean
    - e.g. re-factoring code out into functions
    - e.g. deleting code
  - question authority
    - why? to improve things
    - think for yourself; judge good and bad aspects of code
    - find out why people believe the authority
  - bonus: assume nothing
- misc
  - dropping `\n` char with `strlen()`
  - pointers act weird sometimes
  - C has many inconsistent calling params in its functions
  - asserts and tests are good habits
    - like washing hands before handling food in a restaurant
  - OK to write horrible hacks to get things working first
  - invariant?

## Extra Credit

- [ ] ~~1. The code in the book up to this point (and for the rest of it) potentially violates these rules. Go back and apply what you've learned to one exercise to see if you can improve it or find bugs.~~
  - Skipped
- [ ] ~~2. Find an open source project and give some of the files a similar code review. Submit a patch that fixes a bug.~~
  - Skipped
