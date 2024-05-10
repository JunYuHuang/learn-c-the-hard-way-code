#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>
#include <stdlib.h>

typedef int (*lib_function) (const char *data, int data_length);

int main(int argc, char *argv[])
{
    int rc = 0;
    check(
        argc == 5,
        "USAGE: ex29 libex29.so function data data_length"
    );

    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];
    int data_length = atoi(argv[4]);

    void *lib = dlopen(lib_file, RTLD_NOW);
    check(
        lib != NULL,
        "Failed to open the library %s: %s",
        lib_file,
        dlerror()
    );

    lib_function func = dlsym(lib, func_to_run);
    check(
        func != NULL,
        "Did not find %s function in the library %s: %s",
        func_to_run,
        lib_file,
        dlerror()
    );

    rc = func(data, data_length);
    check(
        rc == 0,
        "Function %s return %d for data: %s and data_length: %d",
        func_to_run,
        rc,
        data,
        data_length
    );

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}
