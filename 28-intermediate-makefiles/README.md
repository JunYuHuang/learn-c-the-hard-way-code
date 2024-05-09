# Exercise 28: Intermediate Makefiles

## Notes

- covers GNU `make
- look up:
  - `make` stuff
    - `patsubst`: ?
- misc
  - watched video to timestamp 8:19
  - `void` data type: ?
  - `void` vs `NULL`
    - ?
  - TODO: fix errors with building use `make`
    - something about undefined refs to various macro functions
      - `dlsym()`
      - `dlerror()`
      - `dlopen()`
      - `dlclose()`
    - missing `<dlfcn.h>` header library in WSL Ubuntu 18.04?

## Extra Credit

- [ ] 1. Try to get the `Makefile` to actually work by putting a source and header file in `src/` and making the library. You shouldn't need a `main` function in the source file.
  - TODO
- [ ] 2. Research what functions the `check:` target is looking for in the `BADFUNCS` regular expression that it's using.
  - TODO
- [ ] ~~3. If you don't do automated unit testing, then go read about it so you're prepared later.~~
  - Skipped
