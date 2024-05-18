# Exercise 38: Hashmap Algorithms

## Notes

- hashing algorithms
  - converts a string into a big non-negative integer
  - may or may not be cryptographically secure
  - rules of thumb for a good hash function
    - has a 1000 mean for making 1000 keys per bucket
    - a tight of a range between its min and max as possible
- code review tips
  - if updated a function, must update all its references
    - can use these tools to help:
      - `cscope`
      - `ack`: like a super fast `grep` for code
  - use `git` commands to help find changes
    - `git status`
    - `git diff`
- misc
  - `/dev/urandom`: Linux file when read returns random bytes
    - bytes are pseudo-randomly generated (RNG)

## Extra Credit

- [ ] ~~1. Take the `default_hash` out of the `hashmap.c`, make it one of the algorithms in `hashmap_algos.c`, and then make all of the tests work again.~~
  - Skipped
- [ ] ~~2. Add the `default_hash` to the `hashmap_algos_tests.c` test and compare its statistics to the other hash functions.~~
  - Skipped
- [ ] ~~3. Find a few more hash functions and add them, too. You can never have too many hash functions!~~
  - Skipped
