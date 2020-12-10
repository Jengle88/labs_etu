#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <locale.h>

#define INCREASE 1.7

char* enter_text(int *cntSnt)
{
	char c;
	int maxSize = 10;
	int size = 0;
	char *text = (char *) malloc(maxSize * sizeof(char));
	int wasAlpha = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '.' || c == ';' || c == '?')
		{
			(*cntSnt)++;
			wasAlpha = 0;
		}
		else if(c != '\t' && c != ' ' && c != '\n')
			wasAlpha = 1;
		else if(!wasAlpha || c == '\n')
			continue;
		if (size + 1 == maxSize)
		{
			char* temp = (char*)realloc(text,(int)(maxSize * INCREASE) * sizeof(char));
			maxSize *= INCREASE;
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
	int cntSnt = 0;
	int cntActualSnt = 0;
	char *text;
	text = enter_text(&cntSnt);
	if(!text)
		return -1;

	//обработка текста
	int oldInd = 0, newInd = 0;
	int cntCapit = 0;
	int size = 0;
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
				text[newInd++] = text[oldInd - size + i];
			cntActualSnt++;
		}
		cntCapit = 0;
		size = 0;
		oldInd++;
	}
	text[newInd] = '\0';

	newInd = 0;
	while(text[newInd] != '\0')
	{
		printf("%c", text[newInd]);
		if(text[newInd] == '.' || text[newInd] == ';' || text[newInd] == '?')
			puts("");
		newInd++;
	}
	cntActualSnt--;
	printf("\nКоличество предложений до %d и количество предложений после %d", cntSnt, cntActualSnt);

	free(text);
	return 0;
}
