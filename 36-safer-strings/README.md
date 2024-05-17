# Exercise 36: Safer Strings

## Notes

- C strings suck
  - impossible to safely process them
  - easy to exploit
- bstring: a 3rd party, better string library
  - `bstring` is an alias for:
    ```c
    struct tagbstring {
        int mlen;
        int slen;
        unsigned char *data;
    };
    ```
- misc
  - `vstr`: another 3rd party string library
  - mostly avoid using `str`- built-in string functions

## Learning The Library

Write tests `tests/bstr_tests.c` for these functions in `bstrlib.c`:

- [x] 1. `bfromcstr`: Create a bstring from a C style constant.
  - See `./mine`
- [ ] 2. `blk2bstr`: Do the same thing, but give the length of the buffer.
  - TODO
- [ ] 3. `bstrcpy`: Copy a bstring.
  - TODO
- [ ] 4. `bassign`: Set one bstring to another.
  - TODO
- [ ] 5. `bassigncstr`: Set a bstring to a C string's contents.
  - TODO
- [ ] 6. `bassignblk`: Set a bstring to a C string but give the length.
  - TODO
- [ ] 7. `bdestroy`: Destroy a bstring.
  - TODO
- [ ] 8. `bconcat`: Concatenate one bstring onto another.
  - TODO
- [ ] 9. `bstricmp`: Compare two bstrings returning the same result as strcmp.
  - TODO
- [ ] 10. `biseq`: Tests if two bstrings are equal.
  - TODO
- [ ] 11. `binstr`: Tells if one bstring is in another.
  - TODO
- [ ] 12. `bfindreplace`: Find one bstring in another, then replace it with a third.
  - TODO
- [ ] 13. `bsplit`: Split a bstring into a bstrList.
  - TODO
- [ ] 14. `bformat`: Do a format string, which is super handy.
  - TODO
- [ ] 15. `blength`: Get the length of a bstring.
  - TODO
- [ ] 16. `bdata`: Get the data from a bstring.
  - TODO
- [ ] 17. `bchar`: Get a char from a bstring.
  - TODO
