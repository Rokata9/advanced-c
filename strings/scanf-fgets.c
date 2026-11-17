#include <stdio.h>
#include <string.h>

static void discard_line(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void read_line(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }

    size_t len = strcspn(buf, "\n");
    if (buf[len] == '\n')
        buf[len] = '\0';
    else
        discard_line();
}

int main()  {
	char str1[32] = "Amol"; 
	char str2[32] = "Sanjay"; 
	char str3[32] = "Rahul"; 

	printf("Enter names of cities:\n");
	if (scanf("%31s %31s %31s", str1, str2, str3) != 3) {
        return 1;
    }
    discard_line();
    printf ("\n %s %s %s \n", str1, str2, str3 ) ;  

	printf("Enter name and surname:\n");
    read_line(str1, sizeof str1);
    puts(str1);
    
    printf("Enter name and surname:\n");
    read_line(str2, sizeof str2);
    puts(str2);

    printf("Enter name and surname:\n");
    read_line(str3, sizeof str3);
    puts(str3);

    return 0;
}
