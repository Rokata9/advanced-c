#include <assert.h>
#include <stdio.h>
#include <string.h>

/* char *xstrcpy(char *target, const char *source) */
/* { */
/* 	assert(target != NULL && source != NULL); */
/* 	char *start = target; */
/* 	while ((*target++ = *source++) != '\0') */
/* 		; */

/* 	return start; */
/* } */

size_t xstrlcpy(char *restrict target, const char *restrict source, size_t size)
{
	assert(target != NULL && source != NULL);
	size_t i = 0;

	if (size > 0) {
		for (; i < size - 1 && source[i] != '\0'; i++)
			target[i] = source[i];
		target[i] = '\0';
	}
	while (source[i] != '\0')
		i++;

	return i;
}

char *xstrcpy_chk(char *target, const char *source, size_t target_size)
{
	size_t need = strlen(source) + 1; // incl. \0
	if (target_size != (size_t)-1 && need > target_size) {
		fprintf(stderr, "xstrcpy needs %zu bytes, target has %zu\n",
			need, target_size);
	}
	return memcpy(target, source, need);
}

#define xstrcpy(t, s) xstrcpy_chk((t), (s), __builtin_object_size((t), 1));

int main()
{
	const char *source = "This is source";
	char target[20];
	xstrcpy(target, source);
	printf("Target is now %s\n", target);

	const char *source2 = "This is second source";
	char target2[10];
	int len = xstrlcpy(target2, source2, 15);
	printf("Total length: %d, copied length: 15, target is %s\n", len,
	       target2);

	return 0;
}
