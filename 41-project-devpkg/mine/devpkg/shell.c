/*
Read the `shell.c` from the bottom to the top (which is a common C
source layout) and you see how I've created the actual `Shell
`variables that you indicated were `extern` in `shell.h`. They live
here, but are available to the rest of the program. This is how you
make global variables that live in one `.o` file but are used
everywhere. You shouldn't make many of these, but they are handy for
things like this.
*/

#include "shell.h"
#include "dbg.h"
#include <stdarg.h>

/*
Finally, I have the `Shell_exec` function, which is a variable
argument function. You've seen this before, but make sure you grasp
the `stdarg.h` functions. In the challenge for this section, you're
going to analyze this function.
*/
int Shell_exec(Shell template, ...)
{
    apr_pool_t *p = NULL;
    int rc = -1;
    apr_status_t rv = APR_SUCCESS;
    va_list argp;
    const char *key = NULL;
    const char *arg = NULL;
    int i = 0;

    rv = apr_pool_create(&p, NULL);
    check(rv == APR_SUCCESS, "Failed to create pool.");

    va_start(argp, template);

    for (
        key = va_arg(argp, const char *);
        key != NULL;
        key = va_arg(argp, const char *)
    ) {
        arg = va_arg(argp, const char *);

        for (i = 0; template.args[i] != NULL; i++) {
            if (strcmp(template.args[i], key) == 0) {
                template.args[i] = arg;
                break;      // found it
            }
        }
    }

    rc = Shell_run(p, &template);
    apr_pool_destroy(p);
    va_end(argp);
    return rc;

error:
    if (p) {
        apr_pool_destroy(p);
    }
    return rc;
}

/*
Continuing up the file we get to the `Shell_run` function, which is
a base function that just runs a command according to what's in a
`Shell` struct. It uses many of the functions defined in
`apr_thread_proc.h`, so go look up each one to see how the base
function works. This seems like a lot of work compared to just using
the `system` function call, but it also gives you more control over
the other program's execution. For example, in our `Shell` struct,
we have a `.dir` attribute that forces the program to be in a
specific directory before running.
*/
int Shell_run(apr_pool_t *p, Shell *cmd)
{
    check(p != NULL, "Invalid pool.");
    check(cmd != NULL, "Invalid command.");
    check(cmd->dir != NULL, "Command dir cannot be NULL.");
    check(cmd->exe != NULL, "Command exe cannot be NULL.");
    check(cmd->args != NULL, "Command args cannot be NULL.");

    apr_procattr_t *attr;
    apr_status_t rv;
    apr_proc_t newproc;

    rv = apr_procattr_create(&attr, p);
    check(rv == APR_SUCCESS, "Failed to create proc attr.");
    check(attr != NULL, "Proc attr should not be NULL.");

    rv = apr_procattr_io_set(
        attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE
    );
    check(rv == APR_SUCCESS, "Failed to set IO of command.");

    rv = apr_procattr_dir_set(attr, cmd->dir);
    check(rv == APR_SUCCESS, "Failed to set root to %s", cmd->dir);

    rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
    check(rv == APR_SUCCESS, "Failed to set cmd type.");

    rv = apr_proc_create(
        &newproc, cmd->exe, cmd->args, NULL, attr, p
    );
    check(rv == APR_SUCCESS, "Failed to run command.");

    rv = apr_proc_wait(
        &newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT
    );
    check(rv == APR_CHILD_DONE, "Failed to wait.");

    check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
    check(
        cmd->exit_why == APR_PROC_EXIT,
        "%s was killed or crashed",
        cmd->exe
    );

    return 0;

error:
    if (p)
        apr_pool_destroy(p);
    return -1;
}

Shell CLEANUP_SH = {
    .dir = "/tmp",
    .exe = "rm",
    .args = {
        "rm",
        "-rf",
        "/tmp/pkg-build",
        "/tmp/pkg-src.tar.gz",
        "/tmp/pkg-src.tar.bz2",
        "/tmp/DEPENDS",
        NULL
    }
};

Shell GIT_SH = {
    .dir = "/tmp",
    .exe = "git",
    .args = { "git", "clone", "URL", "pkg-build", NULL }
};

Shell TAR_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "tar",
    .args = {
        "tar", "-xzf", "FILE", "--strip-components", "1", NULL
    }
};

Shell CURL_SH = {
    .dir = "/tmp",
    .exe = "curl",
    .args = { "curl", "-L", "-o", "TARGET", "URL", NULL }
};

Shell CONFIGURE_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "./configure",
    .args = { "configure", "OPTS", NULL }
};

Shell MAKE_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "make",
    .args = { "make", "OPTS", NULL }
};

Shell INSTALL_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "sudo",
    .args = { "sudo", "make", "TARGET", NULL }
};
