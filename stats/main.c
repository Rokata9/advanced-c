#include <stdio.h>

#include "print_utils.h"
#include "stats.h"

int main(void)
{
	int scores[] = { 4, 8, 15, 16, 23, 42 };
	int count = sizeof(scores) / sizeof(scores[0]);

	print_ints("scores", scores, count);
	printf("average = %.2f\n", average(scores, count));
	return 0;
}
