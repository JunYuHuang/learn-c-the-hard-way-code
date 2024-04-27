// /*
// includes: I include some new header files here to gain access to
// some new functions. What does each give you?
// - `assert.h`: `assert()`
// - `stdlib.h`: `malloc()`, `free()`
// - `string.h`: `strdup()`
// */
// #include <stdio.h>
// #include <assert.h>
// #include <stdlib.h>
// #include <string.h>

// /*
// `struct Person`: This is where I'm creating a structure that has
// four elements to describe a person. The final result is a new
// compound type that lets me reference these elements all as one or
// each piece by name. It's similar to a row of a database table or a
// class in an object-oriented programming (OOP) language.
// */
// struct Person {
//     char *name;
//     int age;
//     int height;
//     int weight;
// };

// /*
// function `Person_create`: I need a way to create these structures,
// so I've made a function to do that. Here are the important things:
// */
// struct Person *Person_create(
//     char *name, int age, int height, int weight
// )
// {

//     /*
//     I use `malloc` for memory allocate to ask the OS to give me a
//     piece of raw memory.

//     I pass to `malloc` the `sizeof(struct Person)`, which calculates
//     the total size of the structure, given all of the fields inside
//     it.
//     */
//     struct Person *who = malloc(sizeof(struct Person));

//     /*
//     I use `assert` to make sure that I have a valid piece of memory
//     back from `malloc`. There's a special constant called `NULL`
//     that you use to mean "unset or invalid pointer." This assert is
//     basically checking that `malloc` didn't return a `NULL` invalid
//     pointer.
//     */
//     assert(who != NULL);

//     /*
//     I initialize each field of `struct Person` using the `x->y`
//     syntax, to say what part of the structure I want to set.

//     I use the `strdup` function to duplicate the string for the
//     name, just to make sure that this structure actually owns it.
//     The `strdup` actually is like `malloc`, and it also copies the
//     original string into the memory it creates.
//     */
//     who->name = strdup(name);
//     who->age = age;
//     who->height = height;
//     who->weight = weight;

//     return who;
// }

// /*
// function `Person_destroy`: If I have a create function, then I
// always need a destroy function, and this is what destroys `Person`
// structures. I again use `assert` to make sure I'm not getting bad
// input. Then I use the function `free` to return the memory I got
// with `malloc` and `strdup`. If you don't do this, you get a memory
// leak.
// */
// void Person_destroy(struct Person *who)
// {
//     assert(who != NULL);

//     free(who->name);
//     free(who);
// }

// /*
// function `Person_print`: I then need a way to print out people,
// which is all this function does. It uses the same `x->y` syntax
// to get the field from the structure to print it.
// */
// void Person_print(struct Person *who)
// {
//     printf("Name: %s\n", who->name);
//     printf("\tAge: %d\n", who->age);
//     printf("\tHeight: %d\n", who->height);
//     printf("\tWeight: %d\n", who->weight);
// }

// /*
// function `main`: In the `main` function, I use all of the previous
// functions and the `struct Person` to do the following:
// */
// int main(int argc, char *argv[])
// {

//     /*
//     Create two people, `joe` and `frank`.
//     */
//     // make two people structures
//     struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

//     struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

//     /*
//     Print them out, but notice I'm using the `%p` format so you can
//     see where the program has actually put your structure in memory.
//     */
//     // print them out and where they are in memory
//     printf("Joe is at memory location %p:\n", joe);
//     Person_print(joe);

//     printf("Frank is at memory location %p:\n", frank);
//     Person_print(frank);

//     /*
//     Age both of them by 20 years with changes to their body, too.
//     */
//     // make everyone age 20 years and print them again
//     joe->age += 20;
//     joe->height -= 2;
//     joe->weight += 40;
//     Person_print(joe);

//     frank->age += 20;
//     frank->weight += 20;

//     /*
//     Print each one after aging them.
//     */
//     // free(frank);
//     Person_print(frank);

//     /*
//     Finally destroy the structures so we can clean up correctly.
//     */
//     // destroy them both so we clean up
//     Person_destroy(joe);
//     Person_destroy(frank);

//     return 0;
// }

// Extra Credit 1 to 3:
// - Update program to NOT use pointers and `malloc()`
//
// References:
// - https://stackoverflow.com/questions/3437404/min-and-max-in-c
// - https://codereview.stackexchange.com/questions/183946/c-code-rewritten-to-use-a-person-struct-without-pointers
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX_SIZE 32
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct Person {
    char name[32];
    int age;
    int height;
    int weight;
};

typedef struct Person Human;

Human Person_create(
    char name[NAME_MAX_SIZE], int age, int height, int weight
)
{
    Human who;

    // initialize the name
    size_t name_size = MIN(strlen(name), NAME_MAX_SIZE);
    memcpy(who.name, name, name_size);
    who.name[name_size + 1] = '\0';

    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(Human who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    Human joe = Person_create("Joe Alex", 32, 64, 140);

    Human frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", &frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    // no need to destroy or free the structs because they
    // live on the stack (and not the heap)

    return 0;
}

