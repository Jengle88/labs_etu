#include "max.h"


int max(int array[], int size)
{
	int maxElement = array[0];
	int i = 0;
	for (i = 1; i < size; ++i)
	{
		if (array[i] > maxElement)
			maxElement = array[i];
	}
	return maxElement;
}
