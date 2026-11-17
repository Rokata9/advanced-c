#include <stdio.h>

int stringToInt(const char *str) {
    int start = 0;
    char first_ch = str[0];

    // allows str to start with '0'
    if (first_ch != '-' && (first_ch < '0' || first_ch > '9')) {
        return -1;
    } else if (first_ch == '-') {
        start = 1;
        ++str;
    }

    int acc = 0;

    for (int i = start; *str != '\0'; str++, i++) {
        if (*str < '0' || *str > '9') {
            return -1;
        } else {
            acc = (acc * 10) + (*str - '0');
        }
    }
    
	return start == 1 ? -acc : acc;
}

int main() {
    char* test = "343";
    int result = stringToInt(test);

    printf("Result: %d", result);
}
