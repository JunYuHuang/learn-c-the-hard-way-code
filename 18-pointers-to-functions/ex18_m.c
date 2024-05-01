/*
The usual `include`s that are needed for all of the functions that
we call.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
Thus us the `die` function from the previous exercise that I'll
use to do error checking.
*/
/** Our old friend die from ex17. */
void die(const char *message)
{
    if (errno) {
      perror(message);
    } else {
      printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb) (int a, int b);

/*
This is where the `typedef` is used, and later I use
`compare_cb` like it's a type similar to `int` or `char` in
`bubble_sort` and `test_sorting`.
*/
/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)

/*
A bubble sort implementation, which is a very
inefficient way to sort some integers. Here's a breakdown:

I use the `typedef` for `compare_cb` as the last
parameter `cmp`. This is now a function that will return a
comparison between two integers for sorting.
*/
{

    /*
    The usual creation of variables on the stack, followed by a
    new array of integers on the heap using `malloc`. Make sure
    you understand what `count * sizeof(int)` is doing.
    */
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target)
        die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    /*
    The outer loop of the bubble sort.
    */
    for (i = 0; i < count; i++) {

        /*
        The inner loop of the bubble sort.
        */
        for (j = 0; j < count - 1; j++) {

            /*
            Now I call the `cmp` callback just like it's a
            normal function, but instead of being the name of
            something that we defined, it's just a pointer to it.
            This lets the caller pass in anything it wants as long
            as it matches the signature of the `compare_cb`
            `typedef`.
            */
            if (cmp(target[j], target[j + 1]) > 0) {

                /*
                The actual swapping operation where a bubble
                sort needs to do what it does.
                */
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    /*
    Finally, this returns the newly created and sorted result
    array `target`.
    */
    return target;
}

/*
Three different versions of the `compare_cb` function type,
which needs to have the same definition as the `typedef` that
we created. The C compiler will complain to you if you get this
wrong and say the types don't match.
*/
int sorted_order(int a, int b)
{
    return (a > b) - (a < b);
}

int reverse_order(int a, int b)
{
    return (a < b) - (a > b);
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/*
This is a tester for the `bubble_sort` function. You can see now
how I'm also using `compare_cb` to pass to `bubble_sort`,
demonstrating how these can be passed around like any other pointers.
*/
/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if (!sorted)
        die("Failed to sort as ascended.");

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

void destroy(compare_cb cmp)
{
    int i = 0;

    unsigned char *data = (unsigned char *)cmp;

    for (i = 0; i < 1; i++) {
        data[i] = i;
    }

    printf("\n");
}

void dump(compare_cb cmp)
{
    int i = 0;

    unsigned char *data = (unsigned char *)cmp;

    for (i = 0; i < 25; i++) {
        printf("%02x:", data[i]);
    }

    printf("\n");
}

/*
A simple `main` function that sets up an array based on
integers to pass on the command line, and then it calls
the `test_sorting` function.
*/
int main(int argc, char *argv[])
{
    if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error.");

    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    /*
    Finally, you get to see how the `compare_cb` function
    pointer `typedef` is used. I simply call `test_sorting` but
    give it the name of `sorted_order`, `reverse_order`, and
    `strange_order` as the function to use. The C compiler then
    finds the address of those functions, and makes it a pointer for
    `test_sorting` to use. If you look at `test_sorting`, you'll see
    that it then passes each of these to `bubble_sort`, but it
    actually has no idea what they do. The compiler only knows that
    they match the `compare_cb` prototype and should work.
    */
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    /*
    Last thing we do is free up the array of numbers that we made.
    */
    free(numbers);

    // printf("SORTED:");
    // dump(sorted_order);

    // destroy(sorted_order);

    // printf("SORTED:");
    // dump(sorted_order);

    return 0;
}
