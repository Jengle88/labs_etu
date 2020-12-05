#include "text.h"

//начальная инициализация текста
int initial_text(Text *new_text, int start_size)
{
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового текста!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	new_text->size = 0;
	new_text->realSize = MAX(start_size, TEXT_START_SIZE);
	new_text->sntcs = (Sentence *) malloc(new_text->realSize * sizeof(Sentence));
	if (new_text->sntcs == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для текста!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	return ALL_OK;
}

//положить назад новое предложение
int push_back_text(Text *text, Sentence *sntc)
{
	//если есть место
	if (text->size < text->realSize)
	{
		text->sntcs[text->size++] = *sntc;
		return ALL_OK;
	}
	//если нет места
	Sentence *tempText = (Sentence *) realloc(text->sntcs, (size_t) (text->realSize * INCREASE) *
														   sizeof(Sentence));
	if (tempText == NULL)
	{
		fwprintf(stderr, L"%sНе получилось выделить память для текста!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
	text->sntcs = tempText;
	text->realSize = (size_t) (text->realSize * INCREASE);
	text->sntcs[text->size++] = *sntc;
	return ALL_OK;
}

//заполнить текст из потока ввода
int fill_text_from_input(Text *text)
{
	wchar_t c = L'$';
	int flag_end_sntc;
	while ((c = getwchar()) != L'@')
	{
		//флаг для признака конца строки
		flag_end_sntc = 0;
		Sentence sntc;
		if (!initial_sntc(&sntc, SNTC_START_SIZE))
			return SOME_ERROR;
		while (!flag_end_sntc)
		{
			Word word;
			if (!initial_word(&word, WORD_START_SIZE))
				return SOME_ERROR;
			//считываем слово до разделителей
			while (!is_sep_symb(c))
			{
				if (!push_back_word(&word, c))
					return SOME_ERROR;
				c = getwchar();
			}
			//добавляем слово в предложение
			if (!push_back_sntc(&sntc, &word))
				return SOME_ERROR;
			//специальное слово с символами разделителями
			Word specWord;
			if (!initial_word(&specWord, WORD_START_SIZE))
				return SOME_ERROR;
			//считываем специальное слово
			while (is_sep_symb(c))
			{
				if (c == L'.') //признак конца строки
					flag_end_sntc = 1;
				if (!push_back_word(&specWord, c))
					return SOME_ERROR;
				c = getwchar();
			}
			if (!push_back_sntc(&sntc, &specWord))
				return SOME_ERROR;
			//если достигли конца предложения
			if (flag_end_sntc)
			{
				//возвращаем лишний символ в поток ввод
				ungetwc(c, stdin);
				if (!push_back_text(text, &sntc))
					return SOME_ERROR;
			}
		}
	}
	return ALL_OK;
}

//удалить предложение из текста
void remove_sent(Text *text, int ind)
{
	//смещаем все предложения после того, которое мы удалили
	for (int i = ind; i < text->realSize - 1; ++i)
	{
		text->sntcs[i] = text->sntcs[i + 1];
	}
	//освобождаем память за последним
	free(text->sntcs[text->realSize - 1].words);
	text->size--;
	text->realSize--;
}

//удалить повторяющиеся предложения
void delete_dubl(Text *text)
{
	for (int i = text->size - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (is_equal_sent(&text->sntcs[i], &text->sntcs[j]))
			{
				remove_sent(text, i);
				break;
			}
		}
	}
}

//получить массив уникальных символов(без знаков препинания)
wchar_t *unique_symb(Text text, int *n)
{
	int tableCntOfENSymb[L'z' - L'a' + 1] = {0}; //массив латинских букв
	int tableCntOfRUSymb[L'я' - L'а' + 1] = {0}; //массив кирилличиских букв
	int size = 0;
	//заполняем массивы и считаем количество различных букв
	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			for (int k = 0; k < text.sntcs[i].words[j].size; ++k)
			{
				wchar_t symb = towlower(text.sntcs[i].words[j].word[k]);
				if (L'a' <= symb && symb <= L'z')
				{
					tableCntOfENSymb[symb - L'a']++;
					if (tableCntOfENSymb[symb - L'a'] == 1)
						size++;
				}
				else if (L'а' <= symb && symb <= L'я')
				{
					tableCntOfRUSymb[symb - L'а']++;
					if (tableCntOfRUSymb[symb - L'а'] == 1)
						size++;
				}
			}
		}
	}
	//массив для ответа
	wchar_t *res = (wchar_t *) malloc(size * sizeof(wchar_t));
	if (!res)
		return SOME_ERROR;

	int ind = 0;
	for (int i = 0; i < L'я' - L'а' + 1; ++i)
	{
		if (tableCntOfRUSymb[i] > 0)
			res[ind++] = L'а' + i;
	}
	for (int i = 0; i < L'z' - L'a' + 1; ++i)
	{
		if (tableCntOfENSymb[i] > 0)
			res[ind++] = L'a' + i;
	}
	//задаём размер массива для ответа
	*n = size;
	return res;
}

//получить массив с количеством слов, длина которых 1, 2, ...
int *unique_len_word(Text text, int *size)
{
	//ищем максимальную длину слова
	int maxSize = -1;
	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (!is_sep_symb(text.sntcs[i].words[j].word[0]))
			{
				maxSize = MAX(maxSize, text.sntcs[i].words[j].size);
			}
		}
	}
	//массив для ответа
	int *res = (int *) calloc(maxSize, sizeof(int));
	if(!res)
		return NULL;

	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (!is_sep_symb(text.sntcs[i].words[j].word[0]))
			{
				res[text.sntcs[i].words[j].size - 1]++;
			}
		}
	}
	//задаём размер массива для ответа
	*size = maxSize;
	return res;
}






//test cases

//abc. abc. abc, eft. abc.@

/*
a. b. a. c.
g. y. z. a, b. c, t. b.@
*/