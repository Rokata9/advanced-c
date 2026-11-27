#include <_abort.h>
#include <_string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

void fibWords(char *strl, int n)
{
	assert(strl != NULL);

	if (n < 0) {
		*strl = '\0';
		return;
	}

	unsigned long len = strlen(strl);
	unsigned long nth = (unsigned long)n;

	if (n == 0 && len >= 2) {
		*strl = 'A';
		++strl;
		*strl = '\0';
		return;
	}

	if (n == 1 && len >= 2) {
		*strl = 'B';
		++strl;
		*strl = '\0';
		return;
	}

	unsigned long need = 1;
	unsigned long prev_size = 1;
	unsigned long curr_size = 1;
	unsigned long temp_size = 0;

	for (unsigned long i = 2; i < nth; i++) {
		need = prev_size + curr_size + 1;

		if (need > len) {
			abort();
			return;
		}

		temp_size = curr_size;
		curr_size = prev_size + curr_size;
		prev_size = temp_size;
	}

	*strl = 'B';
	*(++strl) = 'A';
	// const char *to_append = "B";
	unsigned long running_len = 2;
	char *to_append = malloc(1);

	if (to_append == NULL) {
		perror("Error allocating memory.");
		return;
	}

	*to_append = 'B';

	char *prev_strl = malloc(2);

	if (prev_strl == NULL) {
		perror("Error allocating memory.");
		return;
	}

	*prev_strl = 'B';
	*(++prev_strl) = 'A';

	for (unsigned long i = 3; i <= nth + 1; i++) {
		// 1) save the current strl, later that will be the appendee
		prev_strl = realloc(prev_strl, sizeof(char) * running_len);
		if (prev_strl == NULL) {
			perror("Error re-allocating memory.");
			return;
		}
		strlcpy(prev_strl, strl, sizeof(char) * running_len);

		// 2) append pending appendee to the running result
		strcat(strl, to_append);

		// 3) re-allocate memory for the new appendee, that's the previous strl with len = running_len
		// also save the length of what we appended to update later the running len
		unsigned long to_append_len = strlen(to_append);
		to_append = realloc(to_append, sizeof(char) * running_len);
		strlcpy(to_append, prev_strl, sizeof(char) * running_len);

		running_len += to_append_len;
	}
}

int main()
{
	char fib_word[25];
	fibWords(fib_word, 3);
	puts(fib_word);
}
