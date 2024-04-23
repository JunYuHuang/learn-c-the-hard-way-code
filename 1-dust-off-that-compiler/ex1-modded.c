/*
An `include`, and it is the way to import the contents of one file into this source file. C has a convention of using `.h` extensions for header files, which contain lists of functions to use in your program.
*/
#include <stdio.h>

//
// This is a multi line `comment`, and you could put as many lines of
// text between the opening `/*` and closing `*/` characters as you
// want.
//
/* This is a comment. */

/*
A more complex version of the `main function` you've been using so far. How C programs work is that the operating system loads your program, and then it runs the function named `main`. For the function to be totally complete it needs to return an `int` and take two parameters: an `int` for the argument count and an array of `char *` strings for the arguments. Did that just fly over your head? Don't worry, we'll cover this soon.
*/
int main(int argc, char *argv[])

/*
To start the body of any function, you write a `{` character that indicates the beginning of a block. In Python, you just did a `:` and indented. In other languages, you might have a `begin` or `do` word to start.
*/
{

    /*
    A variable declaration and assignment at the same time. This is how you create a variable, with the syntax type name = value;. In C, statements (except for logic) end in a ';' (semicolon) character.
    */
    int distance = 100;

    /*
    Another kind of comment. It works like in Python or Ruby where the comment starts at the `//` and goes until the end of the line.
    */
    // this is also a comment

    /*
    A call to your old friend `printf`. Like in many languages, function calls work with the syntax `name(arg1, arg2);` and can have no arguments or any number of them. The `printf` function is actually kind of weird in that it can take multiple arguments. You'll see that later.
    */
    printf("You are %d miles away.\n", distance);

    // Extra Credit: Print out 5 more lines of text
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("Hello World! x%d\n", i + 1);
    }

    /*
    A return from the main function that gives the operating system (OS) your exit value. You may not be familiar with how UNIX software uses return codes, so we'll cover that as well.
    */
    return 0;

/*
Finally, we end the main function with a closing brace `}` character, and that's the end of the program.
*/
}
