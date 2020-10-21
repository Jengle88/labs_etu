#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
const int MAX_SIZE = 100;
const int SIZE_ERROR = -1;
const char END_CHAR = '\n';

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