/*
A key design decision for `devpkg` is to have external tools like
`curl`, `tar`, and `git` do most of the work. We could find
libraries to do all of this internally, but it's pointless if we
just need the base features of these programs. There is no shame in
running another command in UNIX.

...

Look at the `shell.h` file to see the structure and the commands
that I'll use. You can see that I'm using `extern` to indicate how
other `.c` files can access variables that I'm defining in `shell.c`.
*/

#ifndef _shell_h
#define _shell_h

#define MAX_COMMAND_ARGS 100

/*
To do this, I'm going to use the `apr_thread_proc.h` functions to
run programs, but I also want to make a simple kind of template
system. I'll use a `struct Shell` that holds all of the information
needed to run a program, but has holes in the arguments list that I
can replace with values.
*/
#include <apr_thread_proc.h>

typedef struct Shell {
    const char *dir;
    const char *exe;

    apr_procattr_t *attr;
    apr_proc_t proc;
    apr_exit_why_e exit_why;
    int exit_code;

    const char *args[MAX_COMMAND_ARGS];
} Shell;

int Shell_run(apr_pool_t *p, Shell *cmd);
int Shell_exec(Shell cmd, ...);

extern Shell CLEANUP_SH;
extern Shell GIT_SH;
extern Shell TAR_SH;
extern Shell CURL_SH;
extern Shell CONFIGURE_SH;
extern Shell MAKE_SH;
extern Shell INSTALL_SH;

#endif
