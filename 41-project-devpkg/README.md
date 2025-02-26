# Exercise 41: Project devpkg

## Notes

- APR: an API library that handles common system calls across different OSs
  - look at the docs
- code review
  - recommended review order:
    1. `devpkg.c`: the main file
    2. `shell.c`
    3. doesn't matter after this

## MVP Notes

- CLI tool with 5 commands

  ```bash
  # Sets up a new installation on a computer.
  devpkg -S

  # Installs a piece of software from a URL.
  devpkg -I <URL>

  # Lists all of the software that has been installed.
  devpkg -L

  # Fetches some source code for manual building.
  devpkg -F

  # Builds the source code and installs it, even if it is
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
- [x] Do Ubuntu-specific configs
  - [x] Add `-D_LARGEFILE64_SOURCE=1` to `CFLAGS` in the `Makefile`
  - [x] Create file `/etc/ld.config.so.d/apr.conf` whose content has the path `/usr/local/apr/lib` in it
  - [x] Run `sudo ldconfig` so it picks up the libraries
  - [x] Verify config worked by checking if running `make` builds and links binary and its dependent libraries
- [x] Create and type-copy `./devpkg/db.h`
- [x] Create and type-copy `./devpkg/db.c`
- [x] Create and type-copy `./devpkg/shell.h`
- [x] Create and type-copy `./devpkg/shell.c`
- [x] Create and type-copy `./devpkg/commands.h`
- [x] Create and type-copy `./devpkg/commands.c`
- [x] Create and type-copy `./devpkg/devpkg.c`

## Challenges

- [x] Challenge 1: Code Review
- [x] Challenge 2: Analyze Shell_exec
- [x] Challenge 3: Critique My Design
- [x] Challenge 4: The README and Test Files
- [ ] ~~Challenge 5: The Final Challenge~~ (skipped)

## Notes For Challenges

### Notes For Challenge 1: Code Review

- formal code review process / steps
  1. start at a changed code part's entry point
  2. verify each function's calling params are right
  3. enter & verify each function's body code is right (line-by-line)
  4. repeat up to step 2 for each function
  5. confirm return values and their usage when exiting functions
  6. confirm any missed calls to changed functions
- code review key points
  - check pointer derefs & defend against `NULL`
  - check `if-statements` and `while-loops` for exiting
  - check if return values will be valid
  - check if allocated memory and other resources are freed
  - confirm all system call params are right via `man` pages
- reviewed checklist
  - [x] `db.h`
  - [x] `db.c`
    - [x] `DB_open()`
    - [x] `DB_close()`
    - [x] `DB_load()`
    - [x] `DB_update()`
    - [x] `DB_find()`
    - [x] `DB_init()`
    - [x] `DB_list()`
- `unistd.h`: a C header that gives POSIX OS API access
  - `access()`
- from `/apr` lib
  - `apr_errno.h`
    - `APR_SUCCESS`: a constant int
    - `apr_status_t`: an int typedef
  - `apr_file_io.h`
    - includes `apr_file_info.h`
      - `APR_UREAD`: a hexadecimal constant
    - includes `apr_errno.h`
    - `apr_dir_make_recursive()`
  - `apr_pools.h`
    - `apr_pool_t`: a struct typedef
    - `apr_pool_initialize()`
    - `apr_pool_create()`
- from `/bstrlib` lib
  - `bread()`: reads a stream into a bstring
  - `bNRead`: a callback type (i.e. function pointer)
  - `BSTR_ERR`: a constant int
  - `BSTR_OK`: a constant int
  - `bdestroy()`
  - `bfromcstr()`
  - `bconchar()`
  - `blength()`
  - `bdata()`

## Notes For Challenge 2: Analyze Shell_exec

- formal code review process / steps
  1. start at a changed code part's entry point
  2. verify each function's calling params are right
  3. enter & verify each function's body code is right (line-by-line)
  4. repeat up to step 2 for each function
  5. confirm return values and their usage when exiting functions
  6. confirm any missed calls to changed functions
- code review key points
  - check pointer derefs & defend against `NULL`
  - check `if-statements` and `while-loops` for exiting
  - check if return values will be valid
  - check if allocated memory and other resources are freed
  - confirm all system call params are right via `man` pages
- tasks
  - [x] code review both `shell.h` and `shell.c`
  - [x] study and add notes for how `Shell_exec()` works
  - [ ] ~~update the code~~ (skipped)
    - [ ] ~~add a `Shell` field that counts all var `args` to be replaced~~
    - [ ]~~ ~~have error check to confirm all these args have been replaced~~
    - [ ] ~~error exit?~~
- code review checklist
  - [x] `shell.h`
  - [x] `shell.c`
    - [x] `Shell_exec()`
    - [x] `Shell_run()`
    - [x] `CLEANUP_SH` struct
    - [x] `GIT_SH` struct
    - [x] `TAR_SH` struct
    - [x] `CURL_SH` struct
    - [x] `CONFIGURE_SH` struct
    - [x] `MAKE_SH` struct
    - [x] `INSTALL_SH` struct
- code review notes
  - from `/apr` lib
    - `apr_thread_proc.h`
      - `apr_procattr_t`: a struct typedef
      - `apr_proc_t`: a struct typedef
      - `apr_exit_why_e`: an enum
      - `apr_procattr_create()`
    - `apr_pools.h`
      - `apr_pool_t`: a struct typedef
    - `apr_errno.h`
      - `apr_status_t`: an int typedef
      - `APR_SUCCESS`: a macro var set to 0
      - `APR_NO_PIPE`: a macro var set to 0
  - from ANSI C standard
    - `stdarg.h`: header lib for variadic functions
- how `Shell_exec()` works
  - `...`: a variadic length string array of elements in the order `[key0, arg0, ..., keyN, argN]`
  - allows passing in optional key-value string pairs in `...` to customize the calling arguments `args` in the `template` `Shell` struct
  - custom values in `...` replace the default values in `template`

### Notes For Challenge 3: Critique My Design

- formal code review process / steps
  1. start at a changed code part's entry point
  2. verify each function's calling params are right
  3. enter & verify each function's body code is right (line-by-line)
  4. repeat up to step 2 for each function
  5. confirm return values and their usage when exiting functions
  6. confirm any missed calls to changed functions
- code review key points
  - check pointer derefs & defend against `NULL`
  - check `if-statements` and `while-loops` for exiting
  - check if return values will be valid
  - check if allocated memory and other resources are freed
  - confirm all system call params are right via `man` pages
- tasks
  - [x] code review both `commands.h` and `commands.c`
  - [x] add improvement notes to `./notes.txt`
- code review checklist
  - [x] `commands.h`
  - [x] `commands.c`
    - [x] `Command_depends()`
    - [x] `Command_fetch()`
    - [x] `Command_build()`
    - [x] `Command_install()`
- code review notes
  - from `/apr` lib
    - `apr_thread_proc.h`
      - `apr_procattr_t`: a struct typedef
      - `apr_proc_t`: a struct typedef
      - `apr_exit_why_e`: an enum
      - `apr_procattr_create()`
    - `apr_pools.h`
      - `apr_pool_t`: a struct typedef
    - `apr_errno.h`
      - `apr_status_t`: an int typedef
      - `APR_SUCCESS`: a macro var set to 0
      - `APR_NO_PIPE`: a macro var set to 0
  - from `/apr-util` lib
    - `apr_uri.h`
      - `apr_uri_t`: a typedef struct
      - `apr_uri_parse()`
    - `apr_fnmatch.h`
      - `apr_fnmatch()`
  - `unistd.h`: a C header that gives POSIX OS API access
    - `access()`

### Notes For Challenge 4: The README and Test Files

- formal code review process / steps
  1. start at a changed code part's entry point
  2. verify each function's calling params are right
  3. enter & verify each function's body code is right (line-by-line)
  4. repeat up to step 2 for each function
  5. confirm return values and their usage when exiting functions
  6. confirm any missed calls to changed functions
- code review key points
  - check pointer derefs & defend against `NULL`
  - check `if-statements` and `while-loops` for exiting
  - check if return values will be valid
  - check if allocated memory and other resources are freed
  - confirm all system call params are right via `man` pages
- tasks
  - [x] code review `devpkg.c`
  - [x] add docs and instructions to `./README`
  - [x] write and test the `devpkg`'s command tests in `test.sh`
- code review checklist
  - [x] `main()`
- code review notes
  - from `/apr` lib
    - `apr_general.h`
      - includes
        - `apr.h`
        - `apr_pools.h`
        - `apr_errno.h`
    - `apr_getopt.h`
      - includes
        - `apr_pools.h`
      - `apr_getopt_t`: a struct typedef
      - `apr_getopt_init()`
    - `apr_strings.h`
      - includes
        - `apr.h`
        - `apr_pools.h`
        - `apr_errno.h`
        - `apr_want.h`
    - `apr_lib.h`
      - includes
        - `apr.h`
        - `apr_errno.h`
    - `apr_pools.h`
      - `apr_pool_t`: a struct typedef
      - `apr_pool_initialize()`
      - `apr_pool_create()`
  - from `/apr-util` lib
    - todo
- doc and instructions notes
  - ran `make install` in `./modded/devpkg`
