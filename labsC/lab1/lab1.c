#include <stdio.h>

const int MAX_SIZE = 100;
const int SIZE_ERROR = -1;
const char END_CHAR = '\n';


int max(int array[], int size);

int min(int array[], int size);

int diff(int array[], int size);

long sum(int array[], int size);


int main()
{
	int command = 0;
	scanf("%d", &command);
	int array[MAX_SIZE];
	int size = 0;
	int inputVar = 0;
	char tempChar = '$';

	while((tempChar = getchar()) != END_CHAR)
	{
		scanf("%d", &inputVar);
		array[size++] = inputVar;
	}

	//проверка для пустого массива
	if(size == 0)
		command = SIZE_ERROR;

	switch (command)
	{
		case 0://Максимальное число
			printf("%d\n", max(array, size));
			break;

		case 1://Минимальное число
			printf("%d\n", min(array, size));
			break;

		case 2://Разность между максимальным и минимальным значением
			printf("%d\n", diff(array, size));
			break;

		case 3://Сумма чисел до первого минимального элемента
			printf("%ld\n", sum(array, size));
			break;

		default://Некорректные данные
			printf("Данные некорректны\n");
	}

	return 0;
}


int max(int array[], int size)
{
	int maxElement = array[0];
	for (int i = 1; i < size; ++i)
	{
		if (array[i] > maxElement)
			maxElement = array[i];
	}
	return maxElement;
}

int min(int array[], int size)
{
	int minElement = array[0];
	for (int i = 1; i < size; ++i)
	{
		if (array[i] < minElement)
			minElement = array[i];
	}
	return minElement;
}

int diff(int array[], int size)
{
	return max(array, size) - min(array, size);
}

long sum(int array[], int size)
{
	int minElement = min(array, size);
	long sumAnswer = 0;
	for (int i = 0; i < size; ++i)
	{
		if (array[i] != minElement)
			sumAnswer += array[i];
		else
			return sumAnswer;
	}
}