#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define SIZE 1000


int comp(const void* a, const void* b)
{
	int A = *((int*)a), B = *((int*)b);
	if(A > B)
		return 1;
	else if (A < B)
		return -1;
	else
		return 0;
}

int main()
{
	int array[SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		scanf("%d", &array[i]);
	}
	qsort(array,SIZE,sizeof(int),comp);

	int key = 0;
	long start_time = clock();
	int *result1 = bsearch(&key,array,SIZE,sizeof(int),comp);
	double time_binsearch = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	if(result1 != NULL)
		printf("exists\n");
	else
		printf("doesn't exist\n");
	//printf("%lf\n", time_binsearch);

	int result2 = -1;
	start_time = clock();
	for (int i = 0; i < SIZE; ++i)
	{
		if(array[i] == key)
			result2 = i;
	}
	double time_brute = (double)(clock() - start_time) / CLOCKS_PER_SEC;
//	if(result2 != -1)
//		printf("exists\n");
//	else
//		printf("doesn't exist\n");
//	printf("%lf\n", time_brute);

	return 0;
}

