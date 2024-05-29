# Exercise 45: A Simple TCP/IP Client

## Notes

- how `select()` works
  - file descriptor (fd): a non-negative integer that id's a file in a UNIX / Linux OS
    - in Linux, everything is a file
    - 0 is always `stdin` (standard input)
    - 1 is always `stdout` (standard output)
    - 2 is always `stderr` (standard error)
  - can create sets of file descriptors
- (network) socket:
  - an abstraction for an app to send and get data over a network
  - like a magical portal or hole
  - set or binded to an IP address and a port number
- code review
  - do light then heavy (formal) review
- misc
  - `sys/select.h`: a POSIX standard C lib that does sync. I/O multiplexing
    - `select()`: lets a program wait until a file descriptor is ready or it catches a signal
    - `fd_set`: a typedef struct
    - `FD_ZERO()`: macro that clears all file descriptors from set
    - `FD_SET()`: macro that adds a file descriptor to set
    - `FD_ISSET()`: macro that check if a file descriptor is in a set
  - `sys/socket.h`: a POSIX standard C lib?
    - `socket()`: makes a communication endpoint
    - `connect()`: start a socket connection
    - `recv()`: gets a message from a socket
  - `sys/types.h`: ?
  - `sys/uio.h`: ?
  - `arpa/inet.h`: ?
  - `netdb.h`: a POSIX standard C lib for doing network address & service translation
    - `addrinfo`: a struct typedef
    - `getaddrinfo()`: makes 1+ `addrinfo` structs
    - `freeaddrinfo()`: destroys `addrinfo`'s made by `getaddrinfo()`
  - `unistd.h`: ?
  - `fcntl.h`: a POSIX standard C lib?
    - `fcntl()`: update a file descriptor
  - recommended book: Snader's Effective TCP/IP Programming
  - nonblocking socket: lets reading or returns data from socket
    - e.g. `O_NONBLOCK` flag in `fcntl()` call inside `nonblock()`
- todos
  - [x] get the copy-pasted source code to compile and build
  - [x] type-copy the source code into `./modded`
  - [x] add code comments to `./modded`
  - [x] read text and add notes here
  - [x] watch video and add notes here

## Extra Credit

- [x] 1. As I mentioned, there are quite a few functions you may not know, so look them up. In fact, look them all up even if you think you know them.
  - Done
- [ ] ~~2. Go back through and add various defensive programming checks to the functions to improve them.~~
  - Skipped
- [ ] ~~3. Use the `getopt` function to allow the user the option not to translate `\n` to `\r\n`. This is only needed on protocols that require it for line endings, like HTTP. Sometimes you don't want the translation, so give the user the option.~~
  - Skipped
