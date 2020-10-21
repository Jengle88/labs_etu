#include "min.h"

int min(int array[], int size)
{
	int minElement = array[0];
	int i = 0;
	for (i = 1; i < size; ++i)
	{
		if (array[i] < minElement)
			minElement = array[i];
	}
	return minElement;
}
