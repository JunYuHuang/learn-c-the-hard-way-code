#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

/*
I'll use this function pointer definition later to call functions in
the library. This is nothing new, but make sure you understand what
it's doing.
*/
typedef int (*lib_function) (const char *data);

int main(int argc, char *argv[])
{
    int rc = 0;
    check(argc == 4, "USAGE: ex29 libex29.so function data");

    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    /*
    After the usual setup for a small program, I use the `dlopen`
    function to load up the library that's indicated by `lib_file`.
    This function returns a handle that we use later, which works a
    lot like opening a file.
    */
    void *lib = dlopen(lib_file, RTLD_NOW);

    /*
    If there's an error, I do the usual check and exit, but notice
    at the end that I'm using `dlerror` to find out what the
    library-related error was.
    */
    check(
        lib != NULL,
        "Failed to open the library %s: %s",
        lib_file,
        dlerror()
    );

    /*
    I use `dlsym` to get a function out of the `lib` by its string
    name in `func_to_run`. This is the powerful part, since I'm
    dynamically getting a pointer to a function based on a string I
    got from the command line `argv`.
    */
    lib_function func = dlsym(lib, func_to_run);
    check(
        func != NULL,
        "Did not find %s function in the library %s: %s",
        func_to_run,
        lib_file,
        dlerror()
    );

    /*
    I then call the `func` function that was returned, and check its
    return value.
    */
    rc = func(data);
    check(
        rc == 0,
        "Function %s return %d for data: %s",
        func_to_run,
        rc,
        data
    );

    /*
    Finally, I close the library up just like I would a file.
    Usually, you keep these open the whole time the program is
    running, so closing it at the end isn't as useful, but I'm
    demonstrating it here.
    */
    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}
