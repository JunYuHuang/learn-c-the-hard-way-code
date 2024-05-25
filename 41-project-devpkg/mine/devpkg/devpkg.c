/*
The last and most important file, but probably the simplest, is
`devpkg.c` which is where the `main` function lives. There's no `.h`
file for this, since it includes all of the others. Instead, this
just creates the executable `devpkg` when combined with the other
`.o` files from our `Makefile`. Enter in the code for this file, and
make sure it's correct.

...

The challenge for this file is to understand how the arguments are
being processed, what the arguments are, and then create the
`README` file with instructions on how to use them. As you write the
`README`, also write a simple `test.sh` that runs `./devpkg` to
check that each command is actually working against real, live code.
Use the `set -e` at the top of your script so that it aborts on the
first error.

Finally, run the program under your debugger and make sure it's working before moving on to the final challenge.
*/

#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

#include "dbg.h"
#include "db.h"
#include "commands.h"

int main(int argc, const char *argv[])
{
    apr_pool_t *p = NULL;
    apr_status_t rv;
    rv = apr_pool_initialize();
    check(rv == APR_SUCCESS, "Failed to initialize pool.");

    rv = apr_pool_create(&p, NULL);
    check(rv == APR_SUCCESS, "Failed to create pool.")

    apr_getopt_t *opt;

    char ch = '\0';
    const char *optarg = NULL;
    const char *config_opts = NULL;
    const char *install_opts = NULL;
    const char *make_opts = NULL;
    const char *url = NULL;
    enum CommandType request = COMMAND_NONE;

    rv = apr_getopt_init(&opt, p, argc, argv);
    check(
        rv == APR_SUCCESS,
        "Failed to initialize arguments for parsing."
    );

    while (
        apr_getopt(
            opt, "I:Lc:m:i:d:SF:B:", &ch, &optarg
        ) == APR_SUCCESS
    ) {
        switch (ch) {
            case 'I':
                request = COMMAND_INSTALL;
                url = optarg;
                break;

            case 'L':
                request = COMMAND_LIST;
                break;

            case 'c':
                config_opts = optarg;
                break;

            case 'm':
                make_opts = optarg;
                break;

            case 'i':
                install_opts = optarg;
                break;

            case 'S':
                request = COMMAND_INIT;
                break;

            case 'F':
                request = COMMAND_FETCH;
                url = optarg;
                break;

            case 'B':
                request = COMMAND_BUILD;
                url = optarg;
                break;
        }
    }

    switch (request) {
        case COMMAND_INSTALL:
            check(url, "You must at least give a URL.");
            Command_install(
                p, url, config_opts, make_opts, install_opts
            );
            break;

        case COMMAND_LIST:
            DB_list();
            break;

        case COMMAND_FETCH:
            check(url != NULL, "You must give a URL.");
            Command_fetch(p, url, 1);
            log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
            break;

        case COMMAND_BUILD:
            check(url, "You must at least give a URL.");
            Command_build(
                p, url, config_opts, make_opts, install_opts
            );
            break;

        case COMMAND_INIT:
            rv = DB_init();
            check(rv == 0, "Failed to make the database.");
            break;

        default:
            sentinel("Invalid command given.");
    }

    return 0;

error:
    if (p) apr_pool_destroy(p);
    return 1;
}
