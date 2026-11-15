#include <stdio.h>
#include <mm_malloc.h>
#include <stdlib.h>

struct myArray {
    int length;
    int numbers[];
};

int main() {
    struct myArray* s = NULL;
    int length;

    printf("How many numbers to allocate? ");
    scanf("%d", &length);

    s = malloc(sizeof(struct myArray) + length * sizeof(int));

    for (int i = 0; i < length; i++) {
        s->numbers[i] = i+1;
    }

    printf("Printing numbers...\n");

    for (int i = 0; i < length; i++) {
        printf("Number at [%d] = %d\n", i, s->numbers[i]);
    }

    free(s);
}
