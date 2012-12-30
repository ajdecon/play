#include <stdio.h>

int main(int argc, char* argv[]) {
    int areas[] = {10,12,13,14,20};
    char name[] = "Adam";
    char full_name[] = {'A','d','a','m',' ','D','e','C','o','n',
        'i','n','c','k','\0'};

    printf("The size of an int: %ld\n",sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld\n",
        sizeof(areas)/sizeof(int));
    printf("The first area is %d, the second is %d\n",
        areas[0], areas[1]);

    printf("The size of a char is %ld\n",sizeof(char));
    printf("The size of name (char[]) is %ld\n",sizeof(name));
    printf("The size of full_name is %ld\n",sizeof(full_name));
    printf("Name is %s, full name is %s\n",name,full_name);

    return 0;

}
