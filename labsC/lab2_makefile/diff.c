#include "diff.h"


int diff(int array[], int size)
{
	return max(array, size) - min(array, size);
}
