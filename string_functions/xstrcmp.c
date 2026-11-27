#include <stdio.h>
#include <assert.h>

int xstrcmp(const char *str1, const char *str2)
{
	assert(str1 != NULL && str2 != NULL);

	const unsigned char *a = (const unsigned char *)str1;
	const unsigned char *b = (const unsigned char *)str2;

	while (*a != '\0' && *a == *b) {
		++a;
		++b;
	}

	// convert to 1, 0 or -1
	return (*a > *b) - (*a < *b);
}

int main()
{
	char *first = "this is tes";
	char *second = "this is test";

	int result = xstrcmp(first, second);

	printf("first compared to second: %d", result);

	//printf("%d", 't' > '\0');

	return 0;
}
