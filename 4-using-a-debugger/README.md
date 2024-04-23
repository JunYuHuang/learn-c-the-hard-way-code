# Exercise 4: Using a Debugger

```bash
# build the binary
make ex3

# run the binary
./ex3

# delete the binary
make clean
```

## Notes

- GDB: a C debugger program for Linux
  - `gdb --batch --ex run --ex q --args [c_binary]`:
    - runs a C binary with backtracing for when it crashes
- LLDB: a C debugger program for OS X
- Valgrind: A C memory checker / debugger for Linux
  - like better version of GDB
  - prereq knowledge to use this:
    - understand the (memory) heap
    - understand memory management
- AddressSanitizer: A C memory checker / debugger for OS X / Linux
  - an alternative for Valgrind
- Splint: a C source code static linter
- misc
  - sometimes hard to crash a C program
  - seg fault
