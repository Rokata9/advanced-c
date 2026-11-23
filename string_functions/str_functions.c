#include <stdio.h>
#include <string.h>

void strncat_() {
    char str1[10] = "Nagpur";
    char str2[] = "Bombay";

    strncat(str1, str2, 3);
    puts(str1);
}

void strcmp_() {
    char str1[] = "Bombaywala";
    char str2[] = "Bombay";

    printf("%d\n", strncmp(str1, str2, 6));
    printf("%d\n", strncmp(str2, str1, 7));
    printf("%d\n", strncmp(str2, str2, 8));
}

void strchr_() {
    char str1[] = "Nagpur";

    printf("%s\n", strchr(str1, 'a'));
    printf("%s\n", strchr(str1, 't'));
}

void strstr_() {
    char str1[] = "I am a boy";
    char str2[] = "am";

    printf("%s", strstr(str1, str2));
}

int main() {
    char str1[4]; 
    char str2[] = "Bombay" ; 
    strncpy(str1, str2, 3);
    str1[3] = '\0';
    puts(str1);


    strncat_();
    strcmp_();
    strchr_();
    strstr_();
    return 0;
}
