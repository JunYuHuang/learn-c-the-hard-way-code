# Exercise 41: Project devpkg

## MVP Notes

- CLI tool with 5 commands

  ```bash
  # Sets up a new installation on a computer.
  devpkg -S

  # Installs a piece of software from a URL.
  devpkg -I <URL>

  # Lists all of the software that's been installed.
  devpkg -L

  # Fetches some source code for manual building.
  devpkg -F

  # Builds the source code and installs it, even if it's
  # already installed.
  devpkg -B
  ```

- is an installer program that works via a software package's URL
- processes a dependency list for each package
- use external commands
- has a simple file DB
- always installs packages at `/usr/local`
- uses commands `configure; make; make install` to install packages
- user can be root
- pre-reqs
  - Apache Portable Runtime (APR) libraries
    - `apr-1.5.2`
    - `apr-util-1.5.4`
- dependencies (5)
  - `bstrlib.o`
  - `db.o`
  - `shell.o`
  - `commands.o`
  - `devpkg`

## Spec Tests

```bash
# TODO
```

## TODOs

- [x] Create and write `./ex41.1.sh` file
- [x] Run `./ex41.1.sh` to install `apr-1.5.2` and `apr-util-1.5.4`
- [x] Create `./devpkg` dir
- [x] Create `./devpkg/README` file
- [x] Create `./devpkg/Makefile` file
- [x] Copy `dbg.h` from exercise 20 to `./devpkg/dbg.h`
- [x] Set up `bstrlib` as a dependency
  - [x] Get and extract the .zip from http://bstring.sourceforge.net/
  - [x] Copy `bstrlib.h` to `./devpkg/bstrlib.h`
  - [x] Copy `bstrlib.c` to `./devpkg/bstrlib.c`
  - [x] Run `make bstrlib.o` to create the `bstrlib.o` file
- [x] Type-copy `./devpkg/Makefile`
- [ ] Do Ubuntu-specific configs
  - [x] Add `-D_LARGEFILE64_SOURCE=1` to `CFLAGS` in the `Makefile`
  - [x] Copy `/usr/local/apr/lib` to `/etc/ld.config.so.d/` ??
  - [x] Run `ldconfig` so it picks up the libraries ??
  - [ ] Verify config worked
- [x] Create and type-copy `./devpkg/db.h`
- [x] Create and type-copy `./devpkg/db.c`
- [ ] Create and type-copy `./devpkg/shell.h`
- [ ] Create and type-copy `./devpkg/shell.c`
- [ ] Create and type-copy `./devpkg/commands.h`
- [ ] Create and type-copy `./devpkg/commands.c`
- [ ] Create and type-copy `./devpkg/devpkg.c`
- [ ] Run `make` in `./devpkg`

## Challenges

- [ ] Challenge 1: Code Review
  - code review notes from exercise 39
    - formal code review process / steps
      1. start at a changed code part's entry point
      2. verify each function's calling params are right
      3. enter & verify each function's body code is right (line-by-line)
      4. repeat up to step 2 for each function
      5. confirm return values and their usage when exiting functions
      6. confirm any missed calls to changed functions
    - code review key points
      - check pointer derefs & defend against `NULL`
      - check `if-statments` and `while-loops` for exiting
      - check if return values will be valid
      - check if allocated memory and other resources are freed
      - confirm all system call params are right via `man` pages
  - notes
    - `unistd.h`: a C header that gives POSIX OS API access
- [ ] Challenge 2: Analyze Shell_exec
  - TODO
- [ ] Challenge 3: Critique My Design
  - TODO
- [ ] Challenge 4: The README and Test Files
  - TODO
- [ ] The Final Challenge
  - [ ] 1. Compare your code to my code available online. Starting with 100%, remove 1% for each line you got wrong.
    - TODO
  - [ ] 2. Take the notes.txt file that you previously created and implement your improvements to the the code and functionality of `devpkg`.
    - TODO
  - [ ] 3. Write an alternative version of `devpkg` using your other favorite language or the one you think can do this the best. Compare the two, then improve your C version of `devpkg` based on what you've learned.
    - TODO

## Notes

- video notes
  - TODO
- misc
  - todo
