#include "word.h"

//начальная инициализация слова
int initial_word(Word *new_word, int start_size)
{
	new_word->size = 0;
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового слова!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	new_word->realSize = MAX(start_size + 1, WORD_START_SIZE);// +1 за счёт \0
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
	if (word->size + 1 < word->realSize) //str + '\0' < str_max
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
	if(word1->size != word2->size || wcscasecmp(word1->word, word2->word) != 0)
		return NOT_EQUAL;
	else
		return EQUAL;
}

//обмен значениями двух слов
void swap_word(Word *word1, Word *word2)
{
	Word tempWord = *word1;
	*word1 = *word2;
	*word2 = tempWord;
}

//сравнение с разделяющими символами
int is_sep_symb(wchar_t c)
{
	return c == L'.' || c == L',' || c == L' ';
}