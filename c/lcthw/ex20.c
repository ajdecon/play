#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>

void test_debug() {
    debug("I have cats.");
    debug("Their names are %s and %s.", "Jazzy", "Mr Darcy");
}

void test_log_err() {
    log_err("This is an error.");
    log_err("Here is %d more", 1);
}

void test_log_warn() {
    log_warn("you can safely ignore this");
    log_warn("Check the logs in %s", "/var/log/messages");
}

void test_log_info() {
    log_info("This could be useful to know: %d", 42);
}

int test_check(char *filename) {
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block); // should work

    input = fopen(filename, "r");
    check(input, "Failed to open %s", filename);
    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) fclose(input);
    return -1;
}

int test_sentinel(int code) {
    char *temp = malloc(100);
    check_mem(temp);

    switch (code) {
        case 1:
            log_info("It worked.");
            break;
        default:
            sentinel("I shouldn't run.");
    }

    free(temp);
    return 0;

error:
    if (temp) free(temp);
    return -1;
}

int test_check_mem() {
    char *test = NULL;
    check_mem(test);
    free(test);
    return 1;
error:
    return -1;
}

int test_check_debug() {
    int i=0;
    check_debug(i!=0, "Oops, I was 0.");
    return 0;
error:
    return -1;
}

int main(int argc, char* argv[]) {
    check(argc==2, "Need an argument.");

    test_debug();
    test_log_err();
    test_log_warn();
    test_log_info();

    check(test_check("ex20.c") == 0, "failed with ex20.c");
    check(test_check(argv[1]) == -1, "failed with argv");
    check(test_sentinel(1) == 0, "test_sentinel failed");
    check(test_sentinel(100) == -1, "test_sentinel failed");
    check(test_check_mem() == -1, "test_check_mem failed");
    check(test_check_debug() == -1, "test_check_debug failed");
    return 0;

error:
    return 1;

}
