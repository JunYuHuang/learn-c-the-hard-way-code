# Exercise 26: Project logfind

## Spec Tests

```bash
# feature 1 test (works with AND'd terms)
./logfind MAX
logfind.c
Makefile

./logfind MAX error
Makefile

# feature 2 test (works with optional OR'd terms)
./logfind -o MAX error
logfind.c
dbg.h
Makefile

# feature 3 test (set allowed log file types in `.logfind` file)
cat .logfind
*.c
*.h
Makefile

# feature 4 test (???)
TODO

# feature 5 test (???)
TODO
```

## Notes

- notes on Zed's solution
  - TODO
- notes for my solution
  - feature 3 (allow log file types in `~./logfind`)
    - `./logfind` is a newline-separated list of allowed log file types
    - example file types: `*.c`, `*.h`, `Makefile`
  - pseudocode
    - store all search terms in a string array `keywords`
      - get from looping thru from 2nd to the last element in `argv`
    - get names of all files in local directory
    - store these names in an array of strings `files`
    - make `res` array that holds the resulting matching file names
    - for each file `f` in `files`,
      - open `f`
      - make int var `matches_count` set to 0
      - loop for each term `word` in `keywords`,
        - move the pointer / cursor position in `f` to it start
        - make int var `word_length` = length of `word`
        - TODO: how to parse lines in a file as a string?
        - TODO: check if current read oart of file matches `f`'s name
      - if `matches_count` == size of `keywords`,
        - push `f`'s string name to `res`
      - close `f`
    - for each file name string `f_name` in `res`,
      - print `f_name` on its own line
- misc
  - can declare AND initialise int index variable inside a for loop
  - stream: a continuous flow of bytes or chars between input and output devices
  - buffer: temp store in memory of input or output data
  - `restrict` qualifier keyword:
    - makes an object (i.e. non-primitive) pointer the only pointer that can access that object
  - for `void` functions,
    - program will run the code under its `error` label even if no code before that label runs fine
    - a fix: make the function return before the `error` label

## `logfind` Tool Features

- [x] 1. This tool takes any sequence of words and assumes I mean "and" for them. So `logfind zedshaw smart guy` will find all files that have `zedshaw` and `smart` and `guy` in them.
  - [x] get all keywords from CLI
  - [x] finds names of all files in current directory of the binary file (`logfind`) using `glob`
- [x] 2. It takes an optional argument of `-o` if the parameters are meant to be _or_ logic.
  - done
- [ ] 3. It loads the list of allowed log files from `~/.logfind`.
  - [x] Make a file `.logfind`
  - [x] Get all file names in cwd if `.logfind` file is not in cwd
  - [ ] If `.logfind` file is in cwd, only get all file names in cwd that match the carriage-return separated patterns in `.logfind`
- [ ] 4. The list of file names can be anything that the `glob` function allows. Refer to `man 3 glob` to see how this works. I suggest starting with just a flat list of exact files, and then add `glob` functionality.
  - TODO
- [x] 5. You should output the matching files as you scan, and try to match them as fast as possible.
  - done
