# Exercise 48: A Simple Network Server

## Notes

- clues
  - use `liblcthw`
  - just make the server (b/c client done already)
  - avoid `select()`; use `fork()` for the server
  - keep it simple; only accept and close a connection
  - stay small, build slowly
- important refs
  - Beej's Guide to Network Programming (an online book)
  - Beej's Guide to Unix Interprocess Communication (an online book)
  - Effective TCP/IP Programming by Jon C. Snader (book)
  - Unix Network Programming (book)
  - search online for "echo server in C"
  - read man (2) pages for:
    - `accept()`
    - `bind()`
    - `listen()`
    - `connect()`
    - `select()`
    - `socket()`
    - `shutdown()`
    - `fork()`
- misc
  - can steal code from `netclient` project in ex47
- todos
  - [x] watch ex48a video
  - [ ] watch ex48b video

## `statserve` Specs

The specification for this project is very simple:

- [ ] 1. Create a simple network server that accepts a connection on port 7899 from `netclient` or the `nc` command, and echoes back anything you type.
- [ ] 2. You'll need to learn how to bind a port, listen on the socket, and answer it. Use your research skills to study how this is done and attempt to implement it yourself.
- [ ] 3. The more important part of this project is laying out the project directory from the `c-skeleton`, and making sure you can build everything and get it working.
- [ ] 4. Don't worry about things like daemons or anything else. Your server just has to run from the command line and keep running.

## Spec Tests

```bash
# Ex48 tests
$ ./bin/statserve 127.0.0.1 7899
$ nc 127.0.0.1 7899
hello world
hello world

# Completed `statserve` tests
$ ./bin/statserve 127.0.0.1 9900 storage
$ nc 127.0.0.1 9900
create /zed 1234
OK
sample /zed 89
661.500000
sample /zed 1
4411.33333
dump /zed
441.333333 ... 124.000000
...
```

## Spec Notes

- TODO

## My Todos

- [ ] TODO
