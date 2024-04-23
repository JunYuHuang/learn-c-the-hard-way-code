# Exercise 6: Memorizing C Syntax

## Notes

- overview notes
  - `ALLCAPS` = replacement spot / hole
  - `[ALLCAPS]` = optional
- execution keywords (11)
  - `goto`: jumps to a label
    - like callback?
- type keywords (9):
  - `long`: long integer
  - `short`: short integer
  - `void`: empty aka null / none??
  - `union`: start a union statement
  - `struct`: groups variables in a single record
    - like objects without methods
  - note: C is weakly typed; it does not enforce types
- data keywords (12): like variable type modifiers
  - `auto`: gives a local variable a local lifetime
  - `enum`: makes a set of int constants
  - `extern`: declares an identifier is defined externally
    - like `any` type in TypeScript??
  - `register`: set a variable in a CPU register
  - `signed`: a signed modifier for integer data types
  - `sizeof`: gets the size of data
  - `typedef`: creates a new type
  - `unsigned`: an unsigned modifier for integer data types
  - `volatile`: declare a variable may be changed elsewhere
- if-statement
- switch-statement
  - works only for integer constants (operands)?
- while-loop
- while with continue
- while with break
- do-while
- for-loop
- enum

  ```c
  enum { CONST1, CONST2, CONST3 } NAME;
  ```

- goto

  ```c
  if (ERROR_TEST) {
      goto fail;
  }

  fail:
      CODE;
  ```

- functions

  ```c
  /*
  TYPE NAME(ARG1, ARG2, ..) {
      CODE;
      return VALUE;
  }
  */
  int name(arg1, arg2) {
      CODE;
      return 0;
  }
  ```

- typedef

  ```c
  // typedef [DEFINITION] [IDENTIFIER];
  typedef unsigned char byte;
  ```

- struct

  ```c
  struct NAME {
      ELEMENTS;
  } [VARIABLE_NAME];
  ```

- typedef struct

  ```c
  typedef struct [STRUCT_NAME] {
      ELEMENTS;
  } IDENTIFIER;
  ```

- union

  - like struct but all its elements overlap in memory

  ```c
  union NAME {
      ELEMENTS;
  } [VARIABLE_NAME];
  ```
