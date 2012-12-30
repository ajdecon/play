#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("You need to use 1 argument.\n");
        return 1;
    }

    int i = 0;
    for(i=0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch(letter) {
            case 'a':
            case 'A':
                printf("%d: A\n",i);
                break;
            case 'e':
            case 'E':
                printf("%d: E\n",i);
            case 'i':
            case 'I':
                printf("%d: E or I\n",i);
                break;
            default:
                printf("Not a case we care for...\n");

        }

    }
    return 0;
}
