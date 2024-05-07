#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include "dbg.h"

// #define MAX_FILE_BYTES 8192
// #define MAX_BUFFER_BYTES 512

typedef enum search_mode { AND, OR } search_mode;

// for stopping the program early
void die(const char *message)
{
    errno ? perror(message) : printf("ERROR: %s\n", message);
    exit(1);
}

// boolean function that returns 1 if true else 0 (false)
int does_match(search_mode mode, int matches_count, int total_count)
{
    if (mode == AND)
        return matches_count == total_count;

    // mode is `OR`
    return matches_count > 0;
}

// boolean function that returns 1 if true else 0 (false)
// int will_open_file(const char *filename)
// {
//     // TODO
//     return 1;
// }

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

    // fill the buffer
    buffer = calloc(1, file_bytes + 1);
    buffer[file_bytes] = '\0';
    check_mem(buffer);

    // read `file` into `buffer`
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

int main(int argc, char *argv[])
{
    search_mode mode = AND;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-o") == 0))
        die("USAGE: logfind [-o] <keyword 1>, ...<keyword N>");

    if (argc > 2 && strcmp(argv[1], "-o") == 0)
        mode = OR;

    // TODO: make hardcoded files dynamically gotten from local dir
    // - get names of all files in local dir whose size < `MAX_BYTES`
    // - store them in an array of strings / char arrays `file_names`
    // - remove first el if `mode` is `OR`
    char *filenames[] = {
        "dbg.h", "logfind.c", "Makefile",
        // "test.sh"
    };

    // OR mode removes el `"-o"` (i.e. `argv[1]`) from the
    // keywords count
    int keywords_count = (mode == OR) ? argc - 2 : argc - 1;

    int matches_count = 0;
    size_t files_count = sizeof(filenames) / sizeof(char *);
    FILE *file;
    char *keyword;
    int rc = 0;

    for (int i = 0; i < files_count; i++) {
        matches_count = 0;

        file = fopen(filenames[i], "r");
        check(file, "Failed to open file.");

        for (int j = 1; j < argc; j++) {
            keyword = argv[j];

            if (is_word_in_file(keyword, file))
                matches_count++;
        }

        rc = fclose(file);
        check(rc == 0, "Failed to close file.");

        if (does_match(mode, matches_count, keywords_count))
            printf("%s\n", filenames[i]);
    }

    return 0;

error:
    die("Program crashed!");
    return -1;
}
