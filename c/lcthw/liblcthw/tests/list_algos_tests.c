#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#undef NDEBUG

char *values[] = {"XXXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

List *create_words() {
    int i = 0;
    List *words = List_create();
    for (i=0; i<NUM_VALUES; i++) {
        List_push(words, values[i]);
    }
    return words;
}



int is_sorted(List *words) {
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && (strcmp(cur->value, cur->next->value) > 0)) {
            debug("Unsorted! %s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }

    }
    return 1;
}

char *test_bubble_sort() {
    List *words = create_words();
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort");

    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc==0, "Bubble sort failed");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort again.");

    List_destroy(words);

    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc==0, "Bubble sort failed on empty list");
    mu_assert(is_sorted(words), "Words should be sorted if empty");

    List_destroy(words);
    return NULL;
}

char *test_merge_sort() {
    log_info("Beginning merge sort test...");
    List *words = create_words();
    List *res = List_merge_sort(words, (List_compare)strcmp);
    log_info("first merge sort complete");

    mu_assert(is_sorted(res), "Words are not sorted after merge sort");

    List *res2 = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort");
    List_destroy(res2);
    List_destroy(res);
    List_destroy(words);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    return NULL;

}

RUN_TESTS(all_tests);
