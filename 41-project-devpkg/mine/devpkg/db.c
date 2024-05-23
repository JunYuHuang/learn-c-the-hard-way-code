#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_io.h>

#include "db.h"
#include "bstrlib.h"
#include "dbg.h"

static FILE *DB_open(const char *path, const char *mode)
{
    check(path != NULL, "Invalid path.");
    check(mode != NULL, "Invalid mode.");

    return fopen(path, mode);

error:
    return NULL;
}

static void DB_close(FILE *db)
{
    check(db != NULL, "Invalid db.");

    fclose(db);

error:
    return;
}

static bstring DB_load()
{
    FILE *db = NULL;
    bstring data = NULL;

    db = DB_open(DB_FILE, "r");
    check(db, "Failed to open database: %s", DB_FILE);

    data = bread((bNread) fread, db);
    check(data, "Failed to read from db file: %s", DB_FILE);

    DB_close(db);
    return data;

error:
    if (db)
        DB_close(db);
    if (data)
        bdestroy(data);
    return NULL;
}

// returns 0 on success or -1 on fail
int DB_update(const char *url)
{
    check(url != NULL, "Invalid url.");

    if (DB_find(url)) {
        log_info("Already recorded as installed: %s", url);
    }

    FILE *db = DB_open(DB_FILE, "a+");
    check(db, "Failed to open DB file: %s", DB_FILE);

    bstring line = bfromcstr(url);
    check(line != NULL, "Invalid url.");

    int rc = 0;
    rc = bconchar(line, '\n');
    check(rc == BSTR_OK, "Failed to append a newline to line.");

    rc = fwrite(line->data, blength(line), 1, db);
    check(rc == 1, "Failed to append to the db.");

    return 0;
error:
    if (db)
        DB_close(db);
    if (line)
        bdestroy(line);
    return -1;
}

// bool function that returns 1 on success or (0 or -1) on fail
int DB_find(const char *url)
{
    check(url != NULL, "Invalid url.");

    bstring data = NULL;
    bstring line = bfromcstr(url);
    check(line != NULL, "Invalid url.");

    int res = -1;

    data = DB_load();
    check(data != NULL, "Failed to load: %s", DB_FILE);

    if (binstr(data, 0, line) == BSTR_ERR) {
        res = 0;
    } else {
        res = 1;
    }

error:          // fallthrough
    if (data)
        bdestroy(data);
    if (line)
        bdestroy(line);

    return res;
}

// returns 0 on success or -1 on fail
int DB_init()
{
    apr_pool_t *p = NULL;

    apr_status_t rc = -1;
    rc = apr_pool_initialize();
    check(rc == APR_SUCCESS, "Failed to initialize database.");

    rc = apr_pool_create(&p, NULL);
    check(rc == APR_SUCCESS, "Failed to create database.");

    if (access(DB_DIR, W_OK | X_OK) == -1) {
        rc = apr_dir_make_recursive(
            DB_DIR,
            APR_UREAD |
            APR_UWRITE |
            APR_UEXECUTE |
            APR_GREAD |
            APR_GWRITE |
            APR_GEXECUTE,
            p
        );
        check(
            rc == APR_SUCCESS,
            "Failed to make database dir: %s",
            DB_DIR
        );
    }

    if (access(DB_FILE, W_OK) == -1) {
        FILE *db = DB_open(DB_FILE, "w");
        check(db, "Cannot open database: %s", DB_FILE);
        DB_close(db);
    }

    apr_pool_destroy(p);
    return 0;

error:
    if (p)
        apr_pool_destroy(p);
    return -1;
}

int DB_list()
{
    bstring data = DB_load();
    check(data, "Failed to read load: %s", DB_FILE);

    printf("%s", bdata(data));
    bdestroy(data);
    return 0;

error:
    if (data)
        bdestroy(data);
    return -1;
}
