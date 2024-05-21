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

## Starter Project TODOs

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
- [ ] Run `make` in `./devpkg`

## Notes

- video notes
  - TODO
- misc
  - 10.5 min video

## `devpkg` Tool Features

- [ ] 1. TODO
  - TODO
