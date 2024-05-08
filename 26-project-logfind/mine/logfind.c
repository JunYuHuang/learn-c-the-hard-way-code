#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <glob.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_STR_LENGTH 8192
#define MAX_BUFFER_BYTES 8192

typedef enum search_mode_t { AND, OR } search_mode_t;

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

glob_t *get_filenames()
{
    int rc = 0;
    int glob_flags = GLOB_MARK;
    glob_t *ptr_glob = malloc(sizeof(glob_t));
    FILE *logfind_file = fopen(".logfind", "r");

    //
    // 1. get all filenames in cwd if can't find `.logfind` file
    //
    if (!logfind_file){
        rc = glob("*", glob_flags, NULL, ptr_glob);
        check(rc == 0, "glob() call failed.");

        return ptr_glob;
    }

    //
    // 2. get all filenames in cwd that match `.logfind`'s patterns
    //
    char *buffer = NULL;
    long buffer_bytes = 0;

    // get `.logfind` file's size in bytes
    rewind(logfind_file);
    rc = fseek(logfind_file, 0, SEEK_END);
    check(
        rc == 0,
        "Failed to move cursor to end of '.logfind' file."
    );
    buffer_bytes = ftell(logfind_file);
    check(
        buffer_bytes != -1L,
        "Failed to get size of '.logfind' file."
    );

    // get the memory for the buffer
    buffer = calloc(1, buffer_bytes + 1);
    check_mem(buffer);

    // read `.logfind` file into `buffer`
    rewind(logfind_file);
    rc = fread(buffer, buffer_bytes, 1, logfind_file);
    check(rc == 1, "Failed to read '.logfind' into buffer.");

    // TODO: get all filenames that matches `.logfile`'s patterns
    // - loop thru each string `str` in `buffer`
    //   - each string is separated by a `\n`
    //   - save string in a char ptr `str` & end it with a null byte
    //   - call glob with `str`

    printf("--> Start of '.logfile' contents:\n");
    for (int i = 0; buffer[i] != '\0'; i++) {
        char ch = buffer[i];
        // printf("%d, ", i);
        // printf("[%c]", buffer[i]);
        // printf("buffer[%i] = '%c'\n", i, buffer[i]);
        if (!ispunct(ch) && !isalnum(ch) && !isblank(ch)) {
            printf("weird char '%c' at pos %d\n", ch, i);
        }
    }
    printf("--> End of '.logfile' contents:\n");

    // char *substring = calloc(1, buffer_bytes + 1);
    // int substring_pos = 0;
    // for (int i = 0; buffer[i] != '\0'; i++) {
    //     char ch = buffer[i];
    //     // if (!isalnum(ch) && !isspace(ch)) continue;
    //     // printf("buffer[%d] = '%c'\n", i, ch);

    //     // found a string pattern's end
    //     if (ch == '\n') {
    //         // debug
    //         printf(
    //             "get_filenames(): found newline at pos %d\n", i
    //         );

    //         // end the substring
    //         substring[substring_pos] = '\0';

    //         // get all filenames that match that pattern
    //         rc = glob(substring, glob_flags, NULL, ptr_glob);
    //         check(rc == 0, "glob() call failed.");
    //         // printf(
    //         //     "get_filenames(): found pattern '%s'\n",
    //         //     substring
    //         // );

    //         // clean up for the next substring
    //         free(substring);
    //         substring = calloc(1, buffer_bytes + 1);
    //         substring_pos = 0;
    //     }
    //     // start or continue building the substring
    //     else {
    //         substring[substring_pos] = ch;
    //         substring_pos++;
    //     }
    // }

    // clean up
    // if (substring)
    //     free(substring);
    rc = fclose(logfind_file);
    check(rc == 0, "Failed to close '.logfind' file.");
    free(buffer);

    // temp: to remove after testing
    rc = glob("*", glob_flags, NULL, ptr_glob);
    check(rc == 0, "glob() call failed.");

    return ptr_glob;

error:
    printf("get_allowed_files(): erred\n");

    if (ptr_glob)
        globfree(ptr_glob);

    if (buffer)
        free(buffer);

    return NULL;
}

int main(int argc, char *argv[])
{
    search_mode_t mode = AND;
    int rc = 0;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-o") == 0))
        die("USAGE: logfind [-o] <pattern 1>, ...<pattern N>");

    if (argc > 2 && strcmp(argv[1], "-o") == 0)
        mode = OR;

    glob_t *results = get_filenames();
    check(results, "Failed to get file names.");

    char **filenames = results->gl_pathv;
    size_t files_count = results->gl_pathc;
    FILE *file;
    char *pattern;

    // set diff params depending on selected mode
    // - AND mode is default
    // - OR mode parses patterns from 3rd el in `argv` (pos 2)
    int patterns_count = (mode == OR) ? argc - 2 : argc - 1;
    int matches_count = 0;

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

    globfree(results);

    return 0;

error:
    if (results)
        globfree(results);

    die("Program crashed!");
    return -1;
}
