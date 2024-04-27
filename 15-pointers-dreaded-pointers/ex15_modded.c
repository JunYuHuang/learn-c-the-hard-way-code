#include <stdio.h>
#include <string.h>

// // The original modded `ex15.c`
// int main_0(int argc, char *argv[])
// {

//     /*
//     Create two arrays: `ages` storing some `int` data, and `names`
//     storing an array of strings.
//     */
//     // create two arrays we care about
//     int ages[] = { 23, 43, 12, 89, 2 };
//     char *names[] = {
//       "Alan", "Frank",
//       "Mary", "John", "Lisa"
//     };

//     /*
//     These are some variables for our `for-loops` later.
//     */
//     // safely get the size of ages
//     int count = sizeof(ages) / sizeof(int);
//     int i = 0;

//     /*
//     This is just looping through the two arrays and printing how
//     old each person is. This is using `i` to index into the array.
//     */
//     // first way using indexing
//     for (i = 0; i < count; i++) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//     }

//     printf("---\n");

//     // setup the pointers to the start of the arrays

//     /*
//     Create a pointer that points at `ages`. Notice the use of
//     `int *` to create a pointer to integer type of pointer.
//     That's similar to `char *`, which is a pointer to char, and a
//     string is an array of chars. Seeing the similarity yet?
//     */
//     int *cur_age = ages;

//     /*
//     Create a pointer that points at `names`. A `char *` is already
//     a pointer to char, so that's just a string. However, you need
//     two levels since `names` is 2-dimensional, which then means you
//     need `char **` for a pointer to (a pointer to char) type. Study
//     that and try to explain it to yourself, too.
//     */
//     char **cur_name = names;

//     /*
//     Loop through `ages` and `names` but use the pointers plus an
//     offset of i instead. Writing `*(cur_name + i)` is the same as
//     writing `name[i]`, and you read it as "the value of (pointer
//     `cur_name` plus i)".
//     */
//     // second way of using pointers
//     for (i = 0; i < count; i++) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//     }

//     printf("---\n");

//     /*
//     This shows how the syntax to access an element of an array
//     is the same for a pointer and an array.
//     */
//     // third way, pointers are just arrays
//     for (i = 0; i < count; i++) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//     }

//     printf("---\n");

//     /*
//     This is another admittedly insane loop that does the same thing
//     as the other two, but instead it uses various pointer arimthetic
//     methods:

//     Initialize our `for-loop` by setting `cur_name` and `cur_age` to
//     the beginning of the `names` and `ages` arrays.

//     The test portion of the `for-loop` then compares the distance of
//     the pointer `cur_age` from the start of `ages`. Why does that
//     work?

//     The increment part of the `for-loop` then increments both
//     `cur_name` and `cur_age` so that they point at the next element
//     of the `name` and `age` arrays.

//     The pointers `cur_name` and `cur_age` are now pointing at one
//     element of the arrays that they work on, and we can print them
//     out using just `*cur_name` and `*cur_age`, which means "the
//     value of whever `cur_name` is pointing".
//     */
//     // fourth way with pointers in a stupid complex way
//     for (
//         cur_name = names,
//         cur_age = ages;
//         (cur_age - ages) < count;
//         cur_name++,
//         cur_age++
//     ) {
//         printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//     }

//     return 0;
// }

// // Extra Credit 1:
// // - Rewrite all of the arrays in this program as pointers.
// int main_1(int argc, char **argv)
// {
//     // create two arrays we care about
//     int ages_array[5];
//     int *ages = ages_array;
//     ages[0] = 23;
//     ages[1] = 43;
//     ages[2] = 12;
//     ages[3] = 89;
//     ages[4] = 2;

//     char names_array[5][sizeof(char) * 8];
//     int **names = names_array;
//     names[0] = "Alan";
//     names[1] = "Frank";
//     names[2] = "Mary";
//     names[3] = "John";
//     names[4] = "Lisa";

//     // safely get the size of ages
//     // int count = sizeof(ages) / sizeof(int);
//     int count = 5;
//     int i = 0;

//     // first way using indexing
//     for (i = 0; i < count; i++) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//     }

//     printf("---\n");

//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // second way of using pointers
//     for (i = 0; i < count; i++) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//     }

//     printf("---\n");

//     // third way, pointers are just arrays
//     for (i = 0; i < count; i++) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//     }

//     printf("---\n");

//     // fourth way with pointers in a stupid complex way
//     for (
//         cur_name = names,
//         cur_age = ages;
//         (cur_age - ages) < count;
//         cur_name++,
//         cur_age++
//     ) {
//         printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//     }

//     return 0;
// }

// // Extra Credit 2:
// // - Rewrite all pointers as arrays
// int main_2(int argc, char *argv[])
// {
//     // create two arrays we care about
//     int ages[] = { 23, 43, 12, 89, 2 };
//     char names[5][8] = {
//       "Alan", "Frank",
//       "Mary", "John", "Lisa"
//     };

//     // safely get the size of ages
//     int count = sizeof(ages) / sizeof(int);
//     int i = 0;

//     // first way using indexing
//     for (i = 0; i < count; i++) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//     }

//     printf("---\n");

//     // setup the pointers to the start of the arrays
//     int cur_age[sizeof(ages)];
//     memcpy(cur_age, ages, sizeof(ages));

//     char cur_name[sizeof(names)][8];
//     memcpy(cur_name, names, 40);

//     // second way of using pointers
//     for (i = 0; i < count; i++) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//     }

//     printf("---\n");

//     // third way, pointers are just arrays
//     for (i = 0; i < count; i++) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//     }

//     printf("---\n");

//     // // fourth way with pointers in a stupid complex way
//     // for (
//     //     cur_name = names,
//     //     cur_age = ages;
//     //     (cur_age - ages) < count;
//     //     cur_name++,
//     //     cur_age++
//     // ) {
//     //     printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//     // }

//     return 0;
// }

// // Extra Credit 4:
// // - process CLI args with just pointers like how `names` was
// // processed
// int main_4(int argc, char *argv[])
// {
//     char **p_argv = argv;
//     int i = 0;

//     for (i = 0; i < argc; i++) {
//         printf("arg %d: '%s'\n", i, p_argv[i]);
//     }

//     return 0;
// }

// // Extra Credit 6:
// // - add a for-loop that prints out the pointers' addresses
// int main_6(int argc, char *argv[])
// {
//     // create two arrays we care about
//     int ages[] = { 23, 43, 12, 89, 2 };
//     char *names[] = {
//       "Alan", "Frank",
//       "Mary", "John", "Lisa"
//     };

//     // safely get the size of ages
//     int count = sizeof(ages) / sizeof(int);
//     int i = 0;

//     // first way using indexing
//     for (i = 0; i < count; i++) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//     }

//     printf("---\n");

//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // second way of using pointers
//     for (i = 0; i < count; i++) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//     }

//     printf("---\n");

//     // third way, pointers are just arrays
//     for (i = 0; i < count; i++) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//     }

//     printf("---\n");

//     // fourth way with pointers in a stupid complex way
//     for (
//         cur_name = names,
//         cur_age = ages;
//         (cur_age - ages) < count;
//         cur_name++,
//         cur_age++
//     ) {
//         printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//         printf("name at %p, age at %p\n", cur_name, cur_age);
//     }

//     return 0;
// }

// // Extra Credit 7:
// // - move prints into their own functions that take in pointers
// void print_1(int count, int *ages, char **names)
// {
//     int i = 0;

//     // first way using indexing
//     for (i = 0; i < count; i++) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//     }
// }

// void print_2(int count, int *ages, char **names)
// {
//     int i = 0;

//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // second way of using pointers
//     for (i = 0; i < count; i++) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//     }
// }

// void print_3(int count, int *ages, char **names)
// {
//     int i = 0;

//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // third way, pointers are just arrays
//     for (i = 0; i < count; i++) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//     }
// }

// void print_4(int count, int *ages, char **names)
// {
//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // fourth way with pointers in a stupid complex way
//     for (
//         cur_name = names,
//         cur_age = ages;
//         (cur_age - ages) < count;
//         cur_name++,
//         cur_age++
//     ) {
//         printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//     }
// }

// int main_7(int argc, char *argv[])
// {
//     // create two arrays we care about
//     int ages[] = { 23, 43, 12, 89, 2 };
//     char *names[] = {
//       "Alan", "Frank",
//       "Mary", "John", "Lisa"
//     };

//     // safely get the size of ages
//     int count = sizeof(ages) / sizeof(int);

//     print_1(count, ages, names);

//     printf("---\n");

//     print_2(count, ages, names);

//     printf("---\n");

//     print_3(count, ages, names);

//     printf("---\n");

//     print_4(count, ages, names);

//     return 0;
// }

// // Extra Credit 8:
// // - Change all for-loops to while-loops
// int main_8(int argc, char *argv[])
// {
//     // create two arrays we care about
//     int ages[] = { 23, 43, 12, 89, 2 };
//     char *names[] = {
//       "Alan", "Frank",
//       "Mary", "John", "Lisa"
//     };

//     // safely get the size of ages
//     int count = sizeof(ages) / sizeof(int);
//     int i = 0;

//     // first way using indexing
//     i = 0;
//     while(i < count) {
//         printf("%s has %d years alive.\n", names[i], ages[i]);
//         i++;
//     }

//     printf("---\n");

//     // setup the pointers to the start of the arrays
//     int *cur_age = ages;
//     char **cur_name = names;

//     // second way of using pointers
//     i = 0;
//     while (i < count) {
//         printf(
//             "%s is %d years old.\n",
//             *(cur_name + i),
//             *(cur_age + i)
//         );
//         i++;
//     }

//     printf("---\n");

//     // third way, pointers are just arrays
//     i = 0;
//     while (i < count) {
//         printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
//         i++;
//     }

//     printf("---\n");

//     // fourth way with pointers in a stupid complex way
//     cur_name = names;
//     cur_age = ages;
//     while ((cur_age - ages) < count) {
//         printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//         cur_name++;
//         cur_age++;
//     }

//     return 0;
// }

int main(int argc, char *argv[])
{
    // main_1(argc, argv); ✅
    // main_2(argc, argv); ✅
    // main_4(argc, argv); ✅
    // main_6(argc, argv); ✅
    // main_7(argc, argv); ✅
    // main_8(argc, argv); ✅
    return 0;
}
