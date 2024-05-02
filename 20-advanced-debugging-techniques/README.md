# Exercise 20: Advanced Debugging Techniques

## Notes

- debug tactics (5):
  - reading code alone cannot debug code
  - repeat bug with an automated test
  - run app with 1 to 3 debug tools
    - i.e.
      - debugger e.g. GDB
      - memory checker e.g. Valgrind
      - linter e.g. lint
  - find backtrace and print all variables in the path
  - after fixing bug, add an assertion to prevent it
    - assertion e.g. Zed's `check()` debug macro
- key debug principle:
  - get more info + make bug happen
- when to use each debug method / tool (3):
  - memory issues -> Valgrind
  - ~90% of logic / usage bugs -> debug printing
  - rest of ~10% bugs OR need more info -> GDB or another debugger
- debug / scientific process:
  - write about bug and its likely causes
  - start debugger with breakpoints for the first cause
  - confirm cause with debugger
  - if cause doesn't cause bug,
    - add notes about result and why
    - repeat from step 2 for next cause
- misc
  - core file: a snapshot of a program's memory before it crashed
    - has info of program's memory and registers at that time
    - why?
      - can get more info when viewed in a debugger
  - extra credit 1: see DDD or an IDE debugger

## Extra Credit

- [ ] ~~Find a graphical debugger and compare using it to raw `gdb`. These are useful when the program you're looking at is local, but they are pointless if you have to debug a program on a server.~~
  - Skipped
- [ ] ~~You can enable core dumps on your OS, and when a program crashes, you'll get a core file. This core file is like a postmortem of the program that you can load up to see what happened right at the crash and what caused it. Change `ex20.c` so that it crashes after a few iterations, then try to get a core dump and analyze it.~~
  - Skipped
