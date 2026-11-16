#include <stdio.h>
#include <string.h>

int main() {
    int a[6] = {3,6,5,10,9,18};
    int b[6];
    memcpy(b, a, sizeof(a));

    for (int i = 0; i < 6; i++) {
        printf("%d ", b[i]);
    }
}
