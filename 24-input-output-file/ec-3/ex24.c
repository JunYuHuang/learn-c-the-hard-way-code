#include <stdio.h>
#include "dbg.h"
#include <string.h>
#include <ctype.h>

#define MAX_DATA 100

// removes all of a string's whitespace and trailing newline chars
void trim(char *string)
{
    // create the new string
    size_t str_size = strlen(string);
    char new_string[MAX_DATA];
    int str_i = 0;
    int new_str_i = 0;
    for (str_i = 0; str_i < str_size; str_i++) {
        if (isspace(string[str_i]))
            continue;
        new_string[new_str_i] = string[str_i];
        new_str_i++;
    }
    new_string[new_str_i] = '\0';

    // update the old string in-place
    size_t new_str_size = strlen(new_string);
    str_i = 0;
    new_str_i = 0;
    for (str_i = 0; str_i < str_size; str_i++) {
        if (str_i < new_str_size) {
            string[str_i] = new_string[str_i];
        } else {
            string[str_i] = '\0';
        }
    }
}

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[])
{
    Person you = {.age = 0 };
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read first name.");
    trim(you.first_name);

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read last name.");
    trim(you.last_name);

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(
        you.eyes <= OTHER_EYES &&
        you.eyes >= 0,
        "Do it right, that's not an option."
    );

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s\n", you.first_name);
    printf("Last Name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}
