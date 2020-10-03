#include <stdio.h>

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
	long sum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (array[i] != minElement)
			sum += array[i];
		else
			return sum;
	}
}

int main()
{
	int command = 0;
	scanf("%d", &command);
	int array[100];
	int size = 0;
	int inputVar = 0;
	int tempChar = getchar()/*считываем лишний пробел*/;

	while (tempChar != '\n')
	{
		tempChar = getchar();
		//проверка для отрицательных чисел
		int sign = 1;//для обработки знака числа
		if (tempChar == '-')
		{
			sign = -1;
			tempChar = getchar();
		}

		inputVar = tempChar - '0';
		while ((tempChar = getchar()) != ' ' && tempChar != '\n')
		{
			inputVar *= 10;
			inputVar += tempChar - '0';
		}

		array[size++] = sign * inputVar;
	}

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

