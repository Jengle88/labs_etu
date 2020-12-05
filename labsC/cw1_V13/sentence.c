#include "sentence.h"


//начальная инициализация предложений
int initial_sntc(Sentence *new_sntc, int start_size)
{
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового предложения!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	new_sntc->size = 0;
	new_sntc->realSize = MAX(start_size, SNTC_START_SIZE);
	new_sntc->words = (Word *) malloc(new_sntc->realSize * sizeof(Word));
	if (new_sntc->words == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для предложения!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	return ALL_OK;
}

//положить назад новое слово
int push_back_sntc(Sentence *sntc, Word *word)
{
	//если есть место
	if (sntc->size < sntc->realSize)
	{
		sntc->words[sntc->size++] = *word;
		return ALL_OK;
	}
	//если нет места
	Word *tempSntc = (Word *) realloc(sntc->words, (size_t) (sntc->realSize * INCREASE) * sizeof(Word));
	if (tempSntc == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для предложения!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	sntc->words = tempSntc;
	sntc->realSize = (size_t) (sntc->realSize * INCREASE);
	sntc->words[sntc->size++] = *word;
	return ALL_OK;
}

//удалить слово из предложения
void remove_word(Sentence *sntc, int ind)
{
	free(sntc->words[ind].word);
	for (int i = ind + 1; i < sntc->realSize; ++i)
	{
		sntc->words[i - 1] = sntc->words[i];
	}
	sntc->size--;
	sntc->realSize--;
}
//фыйФЫЙЦУ, вйцв уйввыйФЫЙцуФЫ, пйцу.@

//проверка предложений на равенство, не учитывая регистр
int is_equal_sent(Sentence *sent1, Sentence *sent2)
{
	if (sent1->size != sent2->size)
		return NOT_EQUAL;
	for (int i = 0; i < sent1->size; ++i)
	{
		if (!is_equal_word(&sent1->words[i], &sent2->words[i]))
			return NOT_EQUAL;
	}
	return EQUAL;
}

//сместить слова на n позиций вперёд
int move_word_n(Sentence *sntc, int n)
{
	n %= (sntc->size / 2);
	int *used = (int*)calloc(sntc->size, sizeof(int));
	if(!used)
		return SOME_ERROR;
	Word swapWord;
	for (int i = sntc->size - 2; i >= 0; i -= 2)
	{
		if(!used[i])//если до этого не были здесь
		{
			int ind = i;
			swapWord = sntc->words[ind]; // запоминаем последнее слово
			do
			{
				//меняем слова местами
				used[ind] = 1;
				sntc->words[ind] = sntc->words[(sntc->size + ind - 2 * n) % sntc->size];
				ind = (sntc->size + ind - 2 * n) % sntc->size;
			} while ((sntc->size + ind - 2 * n) % sntc->size != i);
			used[ind] = 1;
			sntc->words[ind] = swapWord;
		}
	}
	free(used);
	return ALL_OK;
}

//удалить слова с последней заглавной буквой
void rm_word_last_cptlz(Sentence *sntc)
{
	for (int i = sntc->size - 2; i >= 0; i -= 2)
	{
		if (iswupper(sntc->words[i].word[sntc->words[i].size - 1]))
		{//удаляем слово
			remove_word(sntc, i);
			if (i == 0)//если слово было первым, то удаляем его дальнейшие разделители
				remove_word(sntc, i);
			else
			{//если было не первым, то склеиваем разделители и удаляем следующий
				for (int j = 0; j < sntc->words[i].size; ++j)
					push_back_word(&sntc->words[i - 1], sntc->words[i].word[j]);
				remove_word(sntc, i);
			}
		}
	}
}

int is_sep_symb(wchar_t c)
{
	return c == L'.' || c == L',' || c == L' ';
}


//a, b, c. A1, B2, C3.@