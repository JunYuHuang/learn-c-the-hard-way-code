# Exercise 1: Dust Off That Compiler

```bash
# build the binary / executable
make ex1

# run the binary / executable
./ex1
```

## Notes

- installed `lldb-3.9` on WSL Ubuntu 18.04
- building the C source code
  - use `make` tool e.g. `make {c_source_file}`
  - use a C compiler tool e.g. `gcc {c_source_file}`
- how a C program works:
  - OS loads app -> OS calls `main()` function
- always try to fix compiler warnings
- memory issues cause most weird behavior / bugs in C
