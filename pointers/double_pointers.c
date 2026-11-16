#include <stdio.h>

int main() {
    int i = 3;
    int *j;
    j = &i;

    int **k;
    k = &j;

    printf("Address of i: %u\n", *k);
    printf("Address of j: %u\n", k);
    printf("Address of j = %u\n", *&k);
    printf("Address of k = %u\n", &k);

    // Value of i

    // ***&k (right to left) -> address of k -> address of j -> value of j (pointer to i) -> value of i 
    printf("%d %d %d %d %d %d", i, *&i, *j, **&j, **k, ***&k);
}
