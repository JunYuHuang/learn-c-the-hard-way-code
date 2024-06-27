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
    - `socket()`
    - `shutdown()`
    - `fork()`
- misc
  - can steal code from `netclient` project in ex47
  - `sys/select.h`: a POSIX standard C lib that does sync. I/O multiplexing
    - `select()`: lets a program wait until a file descriptor is ready or it catches a signal
    - `fd_set`: a typedef struct
    - `FD_ZERO()`: macro that clears all file descriptors from set
    - `FD_SET()`: macro that adds a file descriptor to set
    - `FD_ISSET()`: macro that check if a file descriptor is in a set
  - `sys/socket.h`: a POSIX standard C lib?
    - `socket()`: makes a communication endpoint
    - `accept()`: accepts a connection on a socket
    - `bind()`: binds a name to a socket
    - `listen()`: listens for connections on a socket
    - `connect()`: start a socket connection
    - `shutdown()`: shut down part of a full-duplex connection
    - `send()`: send a message on a socket
    - `recv()`: gets a message from a socket
  - `sys/types.h`: data types needed for older systems to use socket function calls
  - `sys/uio.h`: vector I/O operation definitions
    - defines `ssize_t` and `size_t` types in `sys/types.h` header
  - `arpa/inet.h`: internet operation definitions
  - `netdb.h`: a POSIX standard C lib for doing network address & service translation
    - `addrinfo`: a struct typedef
    - `getaddrinfo()`: makes 1+ `addrinfo` structs
    - `freeaddrinfo()`: destroys `addrinfo`'s made by `getaddrinfo()`
  - `unistd.h`: standard symbolic constants and types
    - `fork()`: creates a child process
    - `close()`: close a file descriptor
  - `fcntl.h`: a POSIX standard C lib?
    - `fcntl()`: update a file descriptor
  - nonblocking socket: lets reading or returns data from socket
    - e.g. `O_NONBLOCK` flag in `fcntl()` call inside `nonblock()`
- todos
  - [x] watch ex48a video
  - [ ] watch ex48b video

## `statserve` Specs

The specification for this project is very simple:

- [x] 1. Create a simple network server that accepts a connection on port 7899 from `netclient` or the `nc` command, and echoes back anything you type.
- [x] 2. You'll need to learn how to bind a port, listen on the socket, and answer it. Use your research skills to study how this is done and attempt to implement it yourself.
- [x] 3. The more important part of this project is laying out the project directory from the `c-skeleton`, and making sure you can build everything and get it working.
- [x] 4. Don't worry about things like daemons or anything else. Your server just has to run from the command line and keep running.

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

- [x] create a socket
- [x] bind the socket to IP address `127.0.0.1` and port `7899`
- [x] listen to connections on the socket
- [x] accept connections on the socket
- [x] echo back whatever the client types??
- [x] properly shut down server when client sends string message `!quit`
