#include "sentence.h"


//начальная инициализация предложений
int initial_sntc(struct Sentence *new_sntc, int start_size)
{
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового предложения!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	new_sntc->size = 0;
	new_sntc->realSize = MAX(start_size, SNTC_START_SIZE);
	new_sntc->words = (struct Word *) malloc(new_sntc->realSize * sizeof(struct Word));
	if (new_sntc->words == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для предложения!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	return ALL_OK;
}

//положить назад новое слово
int push_back_sntc(struct Sentence *sntc, struct Word *word)
{
	//если есть место
	if (sntc->size + 1 < sntc->realSize)
	{
		sntc->words[sntc->size++] = *word;
		return ALL_OK;
	}
	//если нет места
	struct Word *tempSntc = (struct Word *) realloc(sntc->words,
													(size_t)(sntc->realSize * INCREASE) * sizeof(struct Word));
	if (tempSntc == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для предложения!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	sntc->words = tempSntc;
	sntc->realSize = (size_t) (sntc->realSize * INCREASE);
	sntc->words[sntc->size++] = *word;
	return ALL_OK;
}

//удалить слово из предложения
void remove_word(struct Sentence *sntc, int ind)
{
	for (int i = ind; i < sntc->realSize - 1; ++i)
	{
		sntc->words[i] = sntc->words[i + 1];
	}
	free(sntc->words[sntc->realSize - 1].word);
	sntc->size--;
	sntc->realSize--;
}

//проверка предложений на равенство, не учитывая регистр
int is_equal_sent(struct Sentence *sent1, struct Sentence *sent2)
{
	if (sent1->size != sent2->size)
		return NOT_EQUAL;
	for (int i = 0; i < sent1->size; ++i)
	{
		if(!is_equal_word(&sent1->words[i], &sent2->words[i]))
			return NOT_EQUAL;
	}
	return EQUAL;
}

//сместить слова на n позиций вперёд
void move_word_n(struct Sentence *sntc, int n)
{
	int ind = sntc->size - 2;
	n %= (sntc->size / 2); //убираем лишние круги по смещеию
	struct Word tempWord = sntc->words[ind]; // запоминаем последнее слово
	do
	{
		//меняем слова местами
		sntc->words[ind] = sntc->words[(sntc->size + ind - 2 * n) % sntc->size];
		ind = (sntc->size + ind - 2 * n) % sntc->size;

	} while((sntc->size + ind - 2 * n) % sntc->size != sntc->size - 2);

	//возвращаем слово из temp
	sntc->words[ind] = tempWord;
}

//удалить слова с последней заглавной буквой
void rm_word_last_cptlz(struct Sentence *sntc)
{
	for (int i = sntc->size - 2; i >= 0; i -= 2)
	{
		if(iswupper(sntc->words[i].word[sntc->words[i].size - 1]))
		{
			remove_word(sntc,i);
			if (i == 0)
				remove_word(sntc,i);
			else
			{
				for (int j = 0; j < sntc->words[i].size; ++j)
					push_back_word(&sntc->words[i-1],sntc->words[i].word[j]);
				remove_word(sntc,i);
			}
		}
	}
}


//a, b, c. A1, B2, C3.@