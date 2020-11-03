//WIP
//Сделано:         word.c word.h         - инициал и пуш назад	- проверено
//		   sentence.c sentence.h - инициал и пуш назад	- проверено
//		   text.c text.h 	 - инициал и пуш назад  - проверено

#include "word.h"



int initial_word(struct Word *new_word, int start_size)
{
	if (start_size < 0)
	{
		fprintf(stderr, "%sError, bad start_size for word%s\n", ERROR_CLR, STD_CLR);
		return - 1;
	}
	new_word->size = 0;
	new_word->realSize = MAX(start_size+1, WORD_START_SIZE);
	new_word->word = (wchar_t *) calloc(new_word->realSize, sizeof(wchar_t));
	if(new_word->word == NULL)
	{
		fprintf(stderr, "%sMemory alloc for word failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	return 1;
}


int push_back_word(struct Word *word, wchar_t c)
{
	if (word->size + 1 < word->realSize - 1) //str + 'c' < str_max + '\0'
	{
		word->word[word->size] = c;
		word->word[++word->size] = '\0';
		return 1;
	}
	wchar_t *tempWord = (wchar_t*) realloc(word->word, (size_t)(word->realSize * INCREASE * sizeof(wchar_t)));
	if(tempWord == NULL)
	{
		fprintf(stderr, "%sMemory alloc for word failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	word->word = tempWord;
	word->realSize = (size_t)(word->realSize * INCREASE);
	word->word[word->size] = c;
	word->word[++word->size] = '\0';
	return 1;
}
