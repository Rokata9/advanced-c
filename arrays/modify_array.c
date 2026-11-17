#include <stdio.h>

void modifyArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        *arr = *arr * 3;
        arr++;
    }
}

int main() {
    static int input[] = {-9, 3, -18, 6};
    modifyArray(input, 4);

    for (int i = 0; i < 4; i++) {
        printf("%d\n", input[i]);
    }
}
