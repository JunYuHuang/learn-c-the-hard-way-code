# Exercise 36: Safer Strings

## Notes

- C strings suck
  - impossible to safely process them
  - easy to exploit
- bstring: a 3rd party, better string library

  - `bstring` is a pointer to a `tagbstring` struct:

    ```c
    typedef tagbstring *bstring;

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
- [x] 2. `blk2bstr`: Do the same thing, but give the length of the buffer.
  - See `./mine`
- [ ] ~~3. `bstrcpy`: Copy a bstring.~~
  - Skipped
- [ ] ~~4. `bassign`: Set one bstring to another.~~
  - Skipped
- [ ] ~~5. `bassigncstr`: Set a bstring to a C string's contents.~~
  - Skipped
- [ ] ~~6. `bassignblk`: Set a bstring to a C string but give the length.~~
  - Skipped
- [ ] ~~7. `bdestroy`: Destroy a bstring.~~
  - Skipped
- [ ] ~~8. `bconcat`: Concatenate one bstring onto another.~~
  - Skipped
- [ ] ~~9. `bstricmp`: Compare two bstrings returning the same result as strcmp.~~
  - Skipped
- [ ] ~~10. `biseq`: Tests if two bstrings are equal.~~
  - Skipped
- [ ] ~~11. `binstr`: Tells if one bstring is in another.~~
  - Skipped
- [ ] ~~12. `bfindreplace`: Find one bstring in another, then replace it with a third.~~
  - Skipped
- [ ] ~~13. `bsplit`: Split a bstring into a bstrList.~~
  - Skipped
- [ ] ~~14. `bformat`: Do a format string, which is super handy.~~
  - Skipped
- [ ] ~~15. `blength`: Get the length of a bstring.~~
  - Skipped
- [ ] ~~16. `bdata`: Get the data from a bstring.~~
  - Skipped
- [ ] ~~17. `bchar`: Get a char from a bstring.~~
  - Skipped
