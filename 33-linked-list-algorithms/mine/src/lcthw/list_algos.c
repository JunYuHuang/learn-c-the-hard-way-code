#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>
#include <string.h>

/*
- helper function for `List_bubble_sort()` function
*/
void swap(ListNode *node1, ListNode *node2)
{
    if (node1 == NULL || node2 == NULL) return;
    if (node1 == node2) return;

    void *temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
}

/*
- bubble sort returns 0 on success else -1 on fail
*/
int List_bubble_sort(List *list, List_compare compare_cb)
{
    // handle list edge cases
    if (list == NULL) return 0;
    if (list->count < 2) return 0;
    if (list->first == NULL || list->last == NULL) return 0;
    if (list->first == list->last) return 0;

    int is_swapped = 0; // bool flag
    do {
        is_swapped = 0;

        LIST_FOREACH(list, first, next, cur) {
            if (
                cur->next &&
                compare_cb(cur->value, cur->next->value) > 0
            ) {
                swap(cur, cur->next);
                is_swapped = 1;
            }
        }
    } while (is_swapped);

    return 0;
}

/*
- helper function for `List_merge_sort()`
- the `merge` function merges the left and right sublists
*/
List *merge(List *left, List *right, List_compare compare_cb)
{
    List *result = List_create();
    void *value = NULL;

    while (List_count(left) > 0 && List_count(right) > 0) {
        // is sorted (left node comes before right node)
        if (compare_cb(List_first(left), List_first(right)) <= 0) {
            List_push(result, List_shift(left));
        }
        // is not sorted (left node comes after right node)
        else {
            List_push(result, List_shift(right));
        }
    }

    // Either left or right may have elements left; consume them.
    // (Only one of the following loops will be entered.)
    while (List_count(left) > 0) {
        List_push(result, List_shift(left));
    }
    while (List_count(right) > 0) {
        List_push(result, List_shift(right));
    }

    return result;
}

/*
- merge sort returns the list sorted in-place
- recursively divides the input list into smaller sublists until
the sublists are trivially sorted, and then merges the sublists
while returning up the call chain
*/
List *List_merge_sort(List *list, List_compare compare_cb)
{
    // Base case. A list of zero or one elements is sorted by
    // definition.
    if (List_count(list) < 2)
        return list;

    // Recursive case. First, divide the list into equal-sized
    // sublists consisting of the first half and second half of
    // the list. This assumes lists start at index 0.
    List *left = List_create();
    List *right = List_create();
    int i = 0;
    int mid_pos = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur) {
        if (i < mid_pos) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        i++;
    }

    // Recursively sort both sublists.
    List *new_left = List_merge_sort(left, compare_cb);
    List *new_right = List_merge_sort(right, compare_cb);

    // Clean up.
    if (new_left != left)
        List_destroy(left);
    if (new_right != right)
        List_destroy(right);

    // Then merge the now-sorted sublists.
    List *result = merge(new_left, new_right, compare_cb);
    List_destroy(new_left);
    List_destroy(new_right);
    return result;
}
