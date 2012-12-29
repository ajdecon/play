#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

int main(int argc, char* argv[]) {
    struct node *root;
    struct node *conductor;

    root = malloc(sizeof(struct node));

    root->next = 0;
    root->val = 15;
    conductor = root;

    if (conductor != 0) {
        while (conductor->next != 0) {
            conductor = conductor->next;
        }
    }
    conductor->next = malloc(sizeof(struct node));
    conductor = conductor->next;

    if (conductor == 0) {
        printf("out of memory\n");
        return 1;
    }
    conductor->next = 0;
    conductor->val = 42;
    return 0;
}
