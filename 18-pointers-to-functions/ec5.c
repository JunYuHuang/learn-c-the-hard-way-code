// Extra Credit 5:
// - update `test_sort()` so it ALSO takes in a sort fn as an arg
// - add another sorting function

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

// my custom sort function pointer type
typedef int *(*sort_cb) (int *numbers, int count, compare_cb cmp);

// another sort function based on
// https://www.youtube.com/watch?v=JU767SDMDvA
int *insertion_sort(int *numbers, int count, compare_cb cmp)
{
    // create a new array for the sorted array
    size_t numbers_size = count * sizeof(int);
    int *target = malloc(numbers_size);

    // kill program if there is a memory error
    if (!target)
        die("Memory error.");

    // copy the `numbers` array to the `target` array
    memcpy(target, numbers, numbers_size);

    int i = 1;

    for (i = 1; i < count; i++) {
        int j = i;

        while (j > 0 && cmp(target[j - 1], target[j]) > 0) {
            // swap misordered elements
            int temp = target[j];
            target[j] = target[j - 1];
            target[j - 1] = temp;

            j--;
        }
    }

    return target;
}

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target)
        die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; i++) {
        for (j = 0; j < count - 1; j++) {
            if (cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    return (a == 0 || b == 0) ? 0 : a % b;
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(
    int *numbers, int count, sort_cb sort, compare_cb cmp
)
{
    int i = 0;
    int *sorted = sort(numbers, count, cmp);

    if (!sorted)
        die("Failed to sort as ascended.");

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

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

    printf("Bubble sort:\n");
    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, bubble_sort, strange_order);

    // should print the same as with `bubble_sort()`
    printf("Insertion sort:\n");
    test_sorting(numbers, count, insertion_sort, sorted_order);
    test_sorting(numbers, count, insertion_sort, reverse_order);
    test_sorting(numbers, count, insertion_sort, strange_order);

    free(numbers);

    return 0;
}
