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
- returns 0 on success else -1 on fail
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

// TODO - merge sort
