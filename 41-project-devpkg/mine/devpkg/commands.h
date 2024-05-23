/*
Now you get to make the actual commands that do the work. These
commands will use functions from APR, `db.h`, and `shell.h` to do
the real work of downloading and building the software that you want
it to build. This is the most complex set of files, so do them
carefully. As before, you start by making the `commands.h` file,
then implementing its functions in the `commands.c` file.

There's not much in `commands.h` that you haven't seen already. You
should see that there are some defines for strings that are used
everywhere. The really interesting code is in `commands.c`.
*/

#ifndef _commands_h
#define _commands_h

#include <apr_pools.h>

#define DEPENDS_PATH "/tmp/DEPENDS"
#define TAR_GZ_SRC "/tmp/pkg-src.tar.gz"
#define TAR_BZ2_SRC "/tmp/pkg-src.tar.bz2"
#define BUILD_DIR "/tmp/pkg-build"
#define GIT_PAT "*.git"
#define DEPEND_PAT "*DEPENDS"
#define TAR_GZ_PAT "*.tar.gz"
#define TAR_BZ2_PAT "*.tar.bz2"
#define CONFIG_SCRIPT "/tmp/pkg-build/configure"

enum CommandType {
    COMMAND_NONE, COMMAND_INSTALL, COMMAND_LIST, COMMAND_FETCH,
    COMMAND_INIT, COMMAND_BUILD
};

int Command_fetch(apr_pool_t *p, const char *url, int fetch_only);

int Command_install(
    apr_pool_t *p,
    const char *url,
    const char *configure_opts,
    const char *make_opts,
    const char *install_opts
);

int Command_depends(apr_pool_t *p, const char *path);

int Command_build(
    apr_pool_t *p,
    const char *url,
    const char *configure_opts,
    const char *make_opts,
    const char *install_opts
);

#endif
