#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <locale.h>

#define INCREASE 1.7
#define FALSE 0
#define TRUE 1

char* enter_text(int *cntSent)
{
	char c;
	int maxSize = 10;
	int size = 0;
	char *text = (char *) malloc(maxSize * sizeof(char));
	int wasAlpha = FALSE;//был ли символ до этого (предложение уже началось)
	while ((c = getchar()) != EOF)
	{
		if (c == '.' || c == ';' || c == '?')
		{
			(*cntSent)++;
			wasAlpha = FALSE;//конец предложения
		}
		else if(c != '\t' && c != ' ' && c != '\n')
			wasAlpha = TRUE;//присутствует символ (предложение уже началось)
		else if(!wasAlpha || c == '\n')
			continue;//лишний tab или пробел в начале предложения или \n посередени предложения
		if (size + 1 == maxSize)
		{
			char* temp = (char*)realloc(text,(int)(maxSize * INCREASE) * sizeof(char));
			maxSize *= INCREASE;//увеличиваем кол-во символов в строке
			if(temp)
				text = temp;
			else
				return NULL;
		}
		text[size++] = c;
	}
	text[size] = '\0';
	return text;
}

int main()
{
	setlocale(LC_ALL, "");
	//считывание текста
	int cntSent = 0;
	int cntActualSent = 0;
	char *text;
	text = enter_text(&cntSent);//ввод текста
	if(!text)
		return -1;
	//обработка текста
	int oldInd = 0, newInd = 0;//индекс в старой строке, индекс в новой строке
	int cntCapit = 0;//количество букв в верхнем регистре
	int size = 0;//размер предложения в символах
	while(text[oldInd] != '\0')
	{
		while (text[oldInd] != '.' && text[oldInd] != ';' && text[oldInd] != '?' && text[oldInd] != '!')
		{
			if(isupper(text[oldInd]))
				cntCapit += 1;
			oldInd++;
			size++;
		}
		if(cntCapit < 2)
		{
			for (int i = 0; i < size+1; ++i)//+1 из-за конечного символа(. ? ;)
			{
				text[newInd++] = text[oldInd - size + i];//перемещаем символ из старого индекс в новый
			}
			cntActualSent++;//добавилось предложение
		}
		cntCapit = 0;
		size = 0;
		oldInd++;
	}
	text[newInd] = '\0';
	//вывод текста
	newInd = 0;
	while(text[newInd] != '\0')
	{
		printf("%c", text[newInd]);
		if(text[newInd] == '.' || text[newInd] == ';' || text[newInd] == '?')
			puts("");
		newInd++;
	}
	cntActualSent--;
	printf("\nКоличество предложений до %d и количество предложений после %d", cntSent, cntActualSent);
	//чистим память
	free(text);

	return 0;
}
