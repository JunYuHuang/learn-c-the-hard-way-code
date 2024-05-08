#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <glob.h>
#include "dbg.h"

#define MAX_FILE_BYTES 8192

typedef enum search_mode_t { AND, OR } search_mode_t;

typedef int (*glob_error_cb_t) (const char *epath, int eerrno);

// for stopping the program early
void die(const char *message)
{
    errno ? perror(message) : printf("ERROR: %s\n", message);
    exit(1);
}

// boolean function that returns 1 if true else 0 (false)
int does_match(search_mode_t mode, int matches_count, int total_count)
{
    if (mode == AND)
        return matches_count == total_count;

    // mode is `OR`
    return matches_count > 0;
}

// boolean function that returns 1 if true else 0 (false)
int is_word_in_file(const char *word, FILE *file)
{
    int rc = 0;
    char *buffer = NULL;
    long file_bytes = 0;
    char *word_start_char;

    // get the size of `file` in bytes
    rewind(file);
    rc = fseek(file, 0, SEEK_END);
    check(
        rc == 0,
        "Failed to set file position cursor to end of file."
    );
    file_bytes = ftell(file);
    check(file_bytes != -1L, "Failed to get size of file.");

    // get the memory for the buffer
    buffer = calloc(1, file_bytes + 1);
    buffer[file_bytes] = '\0';
    check_mem(buffer);

    // read / fill `file` into `buffer`
    rewind(file);
    rc = fread(buffer, file_bytes, 1, file);
    check(rc == 1, "Failed to read file into buffer.");

    // check if `word` is a substring in `file`'s contents or not
    word_start_char = strstr(buffer, word);
    free(buffer);
    return word_start_char ? 1 : 0;

error:
    if (buffer)
        free(buffer);
    buffer = NULL;
    return 0;
}

// callback function for calling `glob()`
int glob_error_callback(const char *epath, int eerrno)
{
    printf(
        "glob(): error no. %d at '%s'\n",
        eerrno, epath
    );
    return -1;
}

// TODO:
// - fix `get_allowed_files()` from seg faulting
// - issue seems related to `glob()` and `globfree()` calls
void get_allowed_files(
    // char **results
    // glob_error_cb_t glob_error_cb
)
{
    // TODO:
    // - fetch all files in the cwd of this file (`logfind.c`)
    // - store these files' names in the array `results`
    int rc = 0;
    char *glob_pattern = "*";
    int glob_flags = GLOB_MARK;
    glob_t *ptr_glob = malloc(sizeof(glob_t));
    rc = glob(
        glob_pattern,
        glob_flags,
        NULL,
        ptr_glob
    );
    printf("glob() returned code %d\n", rc);
    check(rc == 0, "glob() call failed.");

    for (int i = 0; i < ptr_glob->gl_pathc; i++) {
        printf(
            "Found pathname: '%s'\n",
            ptr_glob->gl_pathv[i]
        );
    }

    globfree(ptr_glob);

    // char *buffer = NULL;
    // long buffer_bytes = 0;

    // FILE *logfind_file = fopen(".logfind", "r");
    // check(logfind_file, "Failed to open '.logfind' file.");

    // TODO:
    // - read all patterns (one per line) in file `.logfind`
    // - store each pattern string as an element of `results`
    // - store all file names that match the patterns in `filenames`

    // // get the size of `file` in bytes
    // rc = fseek(logfind_file, 0, SEEK_END);
    // check(
    //     rc == 0,
    //     "Failed to move cursor to end of 'logfind' file."
    // );
    // buffer_bytes = ftell(logfind_file);
    // check(
    //     buffer_bytes != -1L,
    //     "Failed to get size of 'logfind' file."
    // );

    // // get the memory for the buffer
    // buffer = calloc(1, buffer_bytes + 1);
    // buffer[buffer_bytes] = '\0';
    // check_mem(buffer);

    // // read / fill `logfind_file` into `buffer`
    // rewind(logfind_file);
    // rc = fread(buffer, buffer_bytes, 1, logfind_file);
    // check(rc == 1, "Failed to read logfind_file into buffer.");

    // printf("'.logfind' contents: \n%s", buffer);

    // rc = fclose(logfind_file);
    // check(rc == 0, "Failed to close '.logfind' file.");

    // if (buffer)
    //     free(buffer);

error:
    printf("get_allowed_files(): erred\n");

    // TODO:
    // - loop thru every string in `results` and free it in memory

    if (ptr_glob) globfree(ptr_glob);

    // if (results)
    //     free(results);

    // if (buffer)
    //     free(buffer);
}

int main(int argc, char *argv[])
{
    search_mode_t mode = AND;
    int rc = 0;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-o") == 0))
        die("USAGE: logfind [-o] <pattern 1>, ...<pattern N>");

    if (argc > 2 && strcmp(argv[1], "-o") == 0)
        mode = OR;

    // TODO: make hardcoded files dynamically gotten from local dir
    // - get all files' names in cwd whose size < `MAX_FILE_BYTES`
    // - store them in an array of strings / char arrays `filenames`
    // - if `.logfind` exists in cwd,
    //   - filter array and only keep file names that match the
    //   regex patterns (each on their own line) in `.logfind`

    // char **results = NULL;
    // get_allowed_files(results, glob_error_callback);
    // get_allowed_files(results);
    get_allowed_files();

    char *filenames[] = {
        "dbg.h", "logfind.c", "Makefile",
        // "test.sh"
    };

    // set diff params depending on selected mode
    // - AND mode is default
    // - OR mode parses patterns from 3rd el in `argv` (pos 2)
    int patterns_count = (mode == OR) ? argc - 2 : argc - 1;

    int matches_count = 0;
    size_t files_count = sizeof(filenames) / sizeof(char *);
    FILE *file;
    char *pattern;

    for (int i = 0; i < files_count; i++) {
        matches_count = 0;

        file = fopen(filenames[i], "r");
        check(file, "Failed to open file.");

        // - OR mode parses patterns from 3rd el in `argv` (pos 2)
        for (int j = (mode == OR) ? 2 : 1; j < argc; j++) {
            pattern = argv[j];

            if (is_word_in_file(pattern, file))
                matches_count++;
        }

        rc = fclose(file);
        check(rc == 0, "Failed to close file.");

        if (does_match(mode, matches_count, patterns_count))
            printf("%s\n", filenames[i]);
    }

    return 0;

error:
    die("Program crashed!");
    return -1;
}
