#include "stats.h"

double average(const int *values, int count)
{
	long sum = 0;

	for (int i = 0; i < count; i++)
		sum += values[i];
	return count > 0 ? (double)sum / count : 0.0;
}
