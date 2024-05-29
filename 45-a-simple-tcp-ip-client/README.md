# Exercise 45: A Simple TCP/IP Client

## Notes

- TODO
- misc
  - 14.5 min video
  - file descriptor (fd): a non-negative integer that id's a file in a UNIX / Linux OS
    - in Linux, everything is a file
    - 0 is always `stdin` (standard input)
    - 1 is always `stdout` (standard output)
    - 2 is always `stderr` (standard error)
  - `fd_set` ???
  - `stdlib.h`
  - `sys/select.h`: a POSIX standard C lib?
    - `select()`: does sync. I/O multiplexing
  - `sys/socket.h`: a POSIX standard C lib?
    - `socket()`: makes a communication endpoint
    - `connect()`: start a socket connection
  - `sys/types.h`: ?
  - `sys/uio.h`: ?
  - `arpa/inet.h`: ?
  - `netdb.h`: a POSIX standard C lib for doing network address & service translation
    - `addrinfo`: a struct typedef
    - `getaddrinfo()`: makes 1+ `addrinfo` structs
    - `freeaddrinfo()`: destroys `addrinfo`'s made by `getaddrinfo()`
    - a
  - `unistd.h`: ?
  - `fcntl.h`: a POSIX standard C lib?
    - `fcntl()`: update a file descriptor
- todos
  - [x] get the copy-pasted source code to compile and build
  - [x] type-copy the source code into `./modded`
  - [x] add code comments to `./modded`
  - [x] read text and add notes here
  - [ ] look up unknown stuff in code and add notes here
  - [ ] watch video and add notes here

## Extra Credit

- [ ] ~~1. As I mentioned, there are quite a few functions you may not know, so look them up. In fact, look them all up even if you think you know them.~~
  - Skipped
- [ ] ~~2. Go back through and add various defensive programming checks to the functions to improve them.~~
  - Skipped
- [ ] ~~3. Use the `getopt` function to allow the user the option not to translate `\n` to `\r\n`. This is only needed on protocols that require it for line endings, like HTTP. Sometimes you don't want the translation, so give the user the option.~~
  - Skipped
