# Exercise 26: Project logfind

## Spec Tests

```bash
# feature 1 test (works with AND\'d terms)
./logfind MAX
logfind.c
Makefile

./logfind MAX error
Makefile

# feature 2 test (works with optional OR\'d terms)
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

## `logfind` Tool Features

- [ ] 1. This tool takes any sequence of words and assumes I mean "and" for them. So `logfind zedshaw smart guy` will find all files that have `zedshaw` and `smart` and `guy` in them.
  - TODO
- [ ] 2. It takes an optional argument of `-o` if the parameters are meant to be or logic.
  - TODO
- [ ] 3. It loads the list of allowed log files from `~/.logfind`.
  - [ ] Make a file `./logfind`
- [ ] 4. The list of file names can be anything that the `glob` function allows. Refer to `man 3 glob` to see how this works. I suggest starting with just a flat list of exact files, and then add `glob` functionality.
  - TODO
- [ ] 5. You should output the matching files as you scan, and try to match them as fast as possible.
  - TODO
