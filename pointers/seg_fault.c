#include <stdio.h>

int main() {
    // Declare pointer variable
    int *p;
    // Typecast constant as pointer using '*' 
    p = (int*) 5684;

    // Display value pointed by p
    printf ("%d" , *p);
}
