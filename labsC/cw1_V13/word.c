#include "word.h"

//начальная инициализация слова
int initial_word(Word *new_word, int start_size)
{
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового слова!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	new_word->size = 0;
	new_word->realSize = MAX(start_size + 1, WORD_START_SIZE);
	new_word->word = (wchar_t *) malloc(new_word->realSize * sizeof(wchar_t));
	if (new_word->word == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для слова!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	return ALL_OK;
}

//положить назад новое слово
int push_back_word(Word *word, wchar_t c)
{
	//если есть место
	if (word->size < word->realSize - 1) //str + 'c' < str_max + '\0'
	{
		word->word[word->size] = c;
		word->word[++word->size] = L'\0';
		return ALL_OK;
	}

	//если нет места
	wchar_t *tempWord = (wchar_t *) realloc(word->word, (size_t) (word->realSize * INCREASE) * sizeof(wchar_t));
	if (tempWord == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для слова!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	word->word = tempWord;
	word->realSize = (size_t) (word->realSize * INCREASE);
	word->word[word->size] = c;
	word->word[++word->size] = L'\0';
	return ALL_OK;
}

//проверка на равенство слов
int is_equal_word(Word *word1, Word *word2)
{
	if(word1->size != word2->size)
		return NOT_EQUAL;
	for (int i = 0; i < word1->size; ++i)
	{
		if (towlower(word1->word[i]) != towlower(word2->word[i]))
			return NOT_EQUAL;
	}
	return EQUAL;
}
