#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>

int List_bubble_sort(List *list, List_compare cmp) {
    int swapped = 1;
    void *tmp = NULL;

    if (List_count(list) <= 1) {
        return 0;
    }

    check(list->first != NULL && list->last != NULL, 
        "List is broken; first or last are NULL");

    while(swapped > 0) {
        swapped = 0;
        LIST_FOREACH(list, first, next, cur) {
            if (cur->next && cmp(cur->value, cur->next->value) > 0) {
                tmp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = tmp;
                swapped = 1; 
            }
        }
    }

    return 0;
error:
    return -1;
}

List *List_merge(List *left, List *right, List_compare cmp) {
    List *result = List_create();;
    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) {
            if (cmp(List_first(left), List_first(right)) < 0) {
                List_push(result, List_shift(left));
            } else {
                List_push(result, List_shift(right));
            }
        } else if (List_count(left) > 0) {
            List_push(result, List_shift(left));
        } else {
            List_push(result, List_shift(right));
        }
    }
    return result;
}

List *List_merge_sort(List *list, List_compare cmp) {
    int middle = 0;
    List *left = List_create();  List *right = List_create();
//    List *newleft = NULL; List *newright = NULL;

    log_info("List_merge_sort starting.");

    if (List_count(list) <= 1) return list;
    middle = List_count(list) / 2;
    log_info("Have selected middle value.");

    LIST_FOREACH(list, first, next, cur) {
        if (middle>0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        middle--;
    }
    log_info("Lists are split");

    List *newleft = List_merge_sort(left, cmp);
    List *newright = List_merge_sort(right, cmp);

    log_info("Calls to List_merge_sort succeeded on left and right.");

    if (newleft != left) List_destroy(left);
    if (newright != right) List_destroy(right);

    return List_merge(newleft, newright, cmp);
}

               
