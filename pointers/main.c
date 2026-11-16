#include <stdio.h>

int main() {
    int i = 3;
    int *j;

    j = &i; // storess adress of i

    printf("Address of i = %u\n", &i);
    printf("Address of i = %u\n", j);
    printf("Address of j = %u\n", &j);

    printf("Value of i = %d\n", i);
    printf("Value of i = %d\n", *(&i));

    // &j - gives address of j
    // *&j - gives what is stored there -> the address of i
    // **&j - gives what is stored in the address of i -> value 3
    printf("Value of i = %d\n", **&j);

    // j stores address of i, de-referencing gets the value there -> 3
    printf("Value of i = %d\n", *j);

    // print address of i directly
    printf("Value of j = %u\n", j);

    // &j - gives address of j
    // *&j - dereferencing gives what is stored there -> address of i
    printf("Value of j = %u\n", *&j);
}
