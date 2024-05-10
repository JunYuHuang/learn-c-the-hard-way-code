# Exercise 28: Intermediate Makefiles

## Notes

- GNU `make` and its Makefiles
  - `$@`: refers to the target name
  - `.PHONY: <target_name>`:
    - target / command that ignores a real file named `target_name`
- more GNU `make` syntax
  - `patsubst`: function that replaces a pattern with text
  - `wildcard`: function that matches a list of patterns
- misc
  - "undefined reference to `dlsym`" problem
    - is a `gcc` C compiler bug
    - Ubuntu 18.04 's `cc` C compiler uses `gcc` under the hood
    - fix: add `-Wl,--no-as-needed -ldl` flags when compiling
      - e.g. `gcc main.c -Wl,--no-as-needed -ldl`
  - `void` type: mostly means no data as a type in C
    - when it prefixes a function,
      - it means the function does not return a value
    - cannot declare variable of type `void`
    - when used as a pointer type,
      - it's like the `any` data type in TypeScript
  - `void` vs `NULL`
    - `NULL`: a special value for a pointer
    - `void`: a special pointer type that refers to a pointer of any valid type (e.g. `int` pointer, etc.)
  - `ar rcs`: runs the `ar` CLI tool with flags `rcs`
    - `ar` tool: makes, updates, and gets from archive files
    - `r` flag: insert files `members...` into archive with replacement
    - `c` flag: create the archive
    - `s` flag: add / update an object-file index to the archive
  - `ranlib`: makes an index or table of contents for an archive
    - same as running `ar -s`

## Extra Credit

- [x] 1. Try to get the `Makefile` to actually work by putting a source and header file in `src/` and making the library. You shouldn't need a `main` function in the source file.
  - See `/modded`
- [x] 2. Research what functions the `check:` target is looking for in the `BADFUNCS` regular expression that it's using.
  - `strncpy()`
  - `strcpy()`
  - `strncat()`
  - `strcat()`
  - `strxfrm()`
  - `strndup()`
  - `strdup()`
  - `strstr()`
  - `strpbrk()`
  - `strtok()`
  - `str_()`?
  - `stpncpy()`
  - `stpcpy()`
  - `snprintf()`
  - `sprintf()`
  - `asprintf()`
  - `byte_()`?
- [ ] ~~3. If you don't do automated unit testing, then go read about it so you're prepared later.~~
  - Skipped
