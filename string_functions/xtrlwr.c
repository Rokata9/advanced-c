#include <assert.h>
#include <stdio.h>

// no restrict - With only one pointer parameter, there's nothing to promise. It's harmless, but it means nothing here.
char *xstrlwr(char *input)
{
	assert(input != NULL);
	for (char *p = input; *p != '\0'; p++) {
		// A to Z might not be contiguous on all machines, e.g. old EBCDIC mainframe
		// for that case use *p = (char)tolower((unsigned char)*p);
		if (*p >= 'A' && *p <= 'Z') {
			*p = *p + ('a' - 'A');
		}
	}
	return input;
}

int main()
{
	char test_input[] = "THIS IS UPPERCASE";
	// passing literal would crash it as literals are placed in readonly memory and can't be modified
	// char *test_input = xstrlwr("HELLO");
	printf("Result in lowercase: %s", xstrlwr(test_input));
}
