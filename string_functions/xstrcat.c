#include <_abort.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

size_t xstrlcat(char *restrict target, const char *restrict source, size_t size)
{
	assert(target != NULL && source != NULL);
	size_t tlen = 0;
	while (tlen < size && target[tlen] != '\0')
		tlen++;

	size_t slen = strlen(source);
	if (tlen == size) { // target had no '\0'
		return size + slen;
	}

	size_t room = size - tlen - 1;
	size_t copy = slen < room ? slen : room;
	memcpy(target + tlen, source, copy);
	target[tlen + copy] = '\0';
	return tlen + slen;
}

char *xstrcat_chk(char *restrict target, const char *restrict source,
		  size_t size)
{
	assert(target != NULL && source != NULL);
	size_t tlen = strlen(target);
	size_t need = tlen + strlen(source) + 1;
	if (size != (size_t)-1 && need > size) {
		fprintf(stderr,
			"xstrcat: result needs %zu bytes, target has %zu\n",
			need, size);
		abort();
	}
	memcpy(target + tlen, source, need - tlen);
	return target;
}

#define xstrcat(t, s) xstrcat_chk((t), (s), __builtin_object_size((t), 1));

int main()
{
	char target[24] = "this is first";
	const char *source = "second";
	const char *result = xstrcat(target, source);
	printf("Concat result: %s\n", result);

	char target2[30] = "[2] this is first";
	const char *source2 = "[2] second";
	int len = xstrlcat(target2, source2, 30);
	printf("Concat result length is: %d\n", len);
}
