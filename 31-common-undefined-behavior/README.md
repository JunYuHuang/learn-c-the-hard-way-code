# Exercise 31: Common Undefined Behavior

## Notes

- UB: Undefined Behavior
  - means compiler can do anything so should avoid it
  - practically also means unspecified behavior
  - kills C as a modern programming language
  - can mostly avoid it by writing clean code but not always
- handy tools
  - Clang's UB helpful flags
  - lint tools and static analyzers
- top 20 UB
  1. refer to an object outside its lifetime
  1. convert to or from an int that makes a value outside its valid range
  1. declare an object or function twice with incompatible types
  1. program tries to update a string literal
  1. divide or mod by zero
  1. try to update a `const`-qualified object / variable
  1. custom header name collision with a standard header
  1. using a `FILE` pointer's pointed-to value after closing the file
  1. and 12 more...

## Extra Credit

- None
