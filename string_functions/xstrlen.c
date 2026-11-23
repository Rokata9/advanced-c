#include <stddef.h>
#include <stdio.h>

size_t xstrlen(const char* str) {
    const char* end = str;

    while (*end != '\0')
        end++;

    return (size_t)(end - str);
}

int main() {
    char* my_str = "This is string";
    int count = xstrlen(my_str);

    printf("Length of string with xstrlen is %d\n", count);
    return 0;
}
