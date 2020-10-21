#include "sum.h"

long sum(int array[], int size)
{
	int minElement = min(array, size);
	long sumAnswer = 0;
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		if (array[i] != minElement)
			sumAnswer += array[i];
		else
			return sumAnswer;
	}
}
