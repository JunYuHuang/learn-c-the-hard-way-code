# Exercise 23: Meet Duff's Device

## Notes

- Duff's device:
  - a hack to loop faster in old C compilers via loop unrolling
  - loop unrolling: speeds up a program via more memory use
  - uses `switch-statement` case fallthrough and a `do-while` loop
  - like sorting toys in groups instead of one-by-one
- misc
  - `% 8` handles ragged amounts / numbers

## Extra Credit

- [x] 1. Never use this again.
  - OK
- [ ] ~~2. Go look at the Wikipedia entry for Duff's device and see if you can spot the error. Read the article, compare it to the version I have here, and try to understand why the Wikipedia code won't work for you but worked for Tom Duff.~~
  - Skipped
- [ ] ~~3. Create a set of macros that lets you create any length of device like this. For example, what if you wanted to have 32 case statements and didn't want to write out all of them? Can you do a macro that lays down eight at a time?~~
  - Skipped
- [ ] ~~4. Change the `main` to conduct some speed tests to see which one is really the fastest.~~
  - Skipped
- [x] 5. Read about `memcpy`, `memmove`, and `memset`, and also compare their speed.
  - `memcpy()`:
    - copies from one place to another
    - memory areas of source and destination can NOT overlap
  - `memmove()`:
    - same as `memcpy()` except source and destination CAN overlap
  - `memset()`:
    - fills first `n` bytes of a memory area with some int or char value
- [x] 6. Never use this again!
  - OK
