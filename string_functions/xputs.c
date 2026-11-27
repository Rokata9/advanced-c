#include <stdio.h>
#include <assert.h>

int xputs(const char *str)
{
	assert(str != NULL);
	int result = 0;

	flockfile(stdout);

	for (; *str != '\0'; ++str) {
		if (putchar_unlocked(*str) == EOF) {
			result = EOF;
			break;
		}
	}

	if (result == 0 && putchar_unlocked('\n') == EOF)
		result = EOF;

	funlockfile(stdout);

	return result;
}

int main()
{
	xputs("my test string");
	return 0;
}
