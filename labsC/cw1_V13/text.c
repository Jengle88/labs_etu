#include "text.h"

//начальная инициализация текста
int initial_text(Text *new_text, int start_size)
{
	new_text->size = 0;
	if (start_size < 0)
	{
		fwprintf(stderr, L"%sОшибка, неверный размер для нового текста!!%s\n", ERROR_CLR, STD_CLR);
		return SOME_ERROR;
	}
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

//удалить предложение из текста
void remove_sent(Text *text, int ind)
{
	//смещаем все предложения после того, которое мы удалили
	for (int i = ind; i < text->realSize - 1; ++i)
	{
		swap_sntc(&(text->sntcs[i]), &(text->sntcs[i + 1]));
	}
	//освобождаем память за последним
	free(text->sntcs[text->realSize - 1].words);
	text->size--;
	text->realSize--;
}

//удалить повторяющиеся предложения
void delete_dubl(Text *text)
{//удаляем с конца для оптимизации (двигаем только те, которые сохранены)
	for (int i = text->size - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (is_equal_sntc(&text->sntcs[i], &text->sntcs[j]))
			{//удаляем предложение, которое имеет больший индекс, и выходим
				remove_sent(text, i);
				break;
			}
		}
	}
}

//освободить всю память
void delete_all(Text *text)
{
	for (int i = 0; i < text->size; ++i)
	{//удаляем до size, тк выделяли память через initial только для [size] элементов
		for (int j = 0; j < text->sntcs[i].size; ++j)
		{
			free(text->sntcs[i].words[j].word);
		}
		free(text->sntcs[i].words);
	}
	free(text->sntcs);
}

//заполнить текст из потока ввода
int input_text(Text *text)
{
	wchar_t c = L'$';
	wchar_t cPrev = L'$';
	int flag_end_sntc;
	while ((c = getwchar()) != L'\n')
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
			while (!is_sep_symb(c) && c != '\n')
			{
				if (!push_back_word(&word, c))
					return SOME_ERROR;
				c = getwchar();
			}
			//добавляем слово в предложение
			if (!push_back_sntc(&sntc, &word))
				return SOME_ERROR;

			//специальное слово с символами разделителями
			Word sepWord;
			if (!initial_word(&sepWord, WORD_START_SIZE))
				return SOME_ERROR;

			//считываем специальное слово
			while (is_sep_symb(c) || (c == L'\n' && cPrev != L'\n'))
			{
				cPrev = c;//запоминаем прошлый разделительный знак

				if (c == L'.') //признак конца строки
					flag_end_sntc = 1;
				if (!push_back_word(&sepWord, c))
					return SOME_ERROR;
				c = getwchar();
			}
			if (!push_back_sntc(&sntc, &sepWord))
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

//вывести текст
void print_text(Text *text)
{
	for (int i = 0; i < text->size; ++i)
	{
		for (int j = 0; j < text->sntcs[i].size; ++j)
		{
			fputws(text->sntcs[i].words[j].word, stdout);
		}
	}
}

//получить массив уникальных символов(без знаков препинания)
wchar_t *unique_symb(Text text, int *n)
{
	int tableCntOfENSymb[L'z' - L'a' + 1] = {0}; //массив количеств латинских букв
	int tableCntOfRUSymb[L'я' - L'а' + 1 + 1] = {0}; //массив количеств кирилличиских букв (+1 за счёт 'ё')
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
				else if (symb == L'ё')
				{
					tableCntOfRUSymb[L'я' - L'а' + 1]++;
					if (tableCntOfRUSymb[L'я' - L'а' + 1] == 1)
						size++;
				}
			}
		}
	}
	//массив для ответа
	wchar_t *res = (wchar_t *) malloc(size * sizeof(wchar_t));
	if (!res)
		return NULL;

	int ind = 0;
	for (int i = 0; i < L'я' - L'а' + 1; ++i)
	{
		if (L'е' - L'а' + 1 == i && tableCntOfRUSymb[L'я' - L'а' + 1] > 0)
			res[ind++] = L'ё';
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
	int maxSize = 0;
	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (!is_sep_symb(text.sntcs[i].words[j].word[0]) && text.sntcs[i].words[j].word[0] != L'\n')
			{
				maxSize = MAX(maxSize, text.sntcs[i].words[j].size);
			}
		}
	}
	//массив для ответа
	int *res = (int *) calloc(maxSize, sizeof(int));
	if (!res)
		return NULL;

	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (!is_sep_symb(text.sntcs[i].words[j].word[0]) && text.sntcs[i].words[j].word[0] != L'\n')
			{
				res[text.sntcs[i].words[j].size - 1]++;
			}
		}
	}
	//задаём размер массива для ответа
	*size = maxSize;
	return res;
}


//сравнение слов
int comp_word_cnt(const void *a, const void *b)
{
	Word_cnt *word1 = (Word_cnt*)a;
	Word_cnt *word2 = (Word_cnt*)b;
	if(word1->cnt > word2->cnt)//в порядке убывания
		return -1;
	else if(word1->cnt < word2->cnt)
		return 1;
	else
		return 0;
}

//сортировка слов по частоте встречаемости и удаление
Word_cnt *sort_word_by_cnt(Text *text, int *size)
{
	if (text->size == 0)
		return NULL;
	int cntWord = 0;
	for (int i = 0; i < text->size; ++i)
	{
		cntWord += text->sntcs[i].size / 2;
	}
	Word *arr = (Word *) malloc(cntWord * sizeof(Word));
	if(arr == NULL)
		return NULL;
	int ind = 0;
	for (int i = 0; i < text->size; ++i)
	{
		for (int j = 0; j < text->sntcs[i].size; j += 2)
		{
			arr[ind++] = text->sntcs[i].words[j];
		}
	}
	qsort(arr, cntWord, sizeof(Word), cmp_word);

	int tableCapacity = 10;
	int tableSize = 0;
	struct word_cnt *tableWord = malloc(tableCapacity * sizeof(struct word_cnt));
	if(tableWord == NULL)
	{
		free(arr);
		return NULL;
	}
	tableWord[0].word = (Word*)malloc(10 * sizeof(Word));
	if(tableWord[0].word == NULL)
	{
		free(arr);
		free(tableWord);
		return NULL;
	}
	tableWord[0].word[0] = arr[0];
	tableWord[0].word_capacity = 10;
	tableWord[0].cnt = 1;
	for (int i = 1; i < cntWord; ++i)//aa, aa, aa, bb, bb.
	{
		if (cmp_word(&(arr[i].word), &(arr[i - 1].word)) == 0)
		{
			if(tableWord[tableSize].word_capacity == tableWord[tableSize].cnt + 1)
			{
				Word* tempWord = (Word*)realloc(tableWord[tableSize].word, (size_t)(tableWord[tableSize].word_capacity * INCREASE));
				if(tempWord != NULL)
				{
//					tableWord[tableSize].word[tableWord[tableSize].cnt] = arr[i];
					tableWord[tableSize].word_capacity *= INCREASE;
				}
				else
				{
					free(tableWord);
					free(arr);
					return NULL;
				}
			}
			tableWord[tableSize].word[tableWord[tableSize].cnt] = arr[i];
			tableWord[tableSize].cnt++;
		}
		else
		{
			if (tableSize + 1 == tableCapacity)
			{
				struct word_cnt *tempTable = (struct word_cnt *) realloc(tableWord,
																		 (size_t) (tableCapacity * INCREASE));
				if(tempTable == NULL)
				{
					free(arr);
					return NULL;
				}
				else
				{
					tableWord = tempTable;
					tableCapacity = (size_t) (tableCapacity * INCREASE);
				}
			}
			tableSize++;
			tableWord[tableSize].word = (Word*)malloc(10 * sizeof(Word));
			tableWord[tableSize].word[0] = arr[i];
			tableWord[tableSize].word_capacity = 10;
			tableWord[tableSize].cnt = 1;
		}
	}
	qsort(tableWord, tableSize + 1, sizeof(Word_cnt), comp_word_cnt);
	ind = 0;
	for (int i = 0; i < text->size; ++i)
	{
		for (int j = 0; j < text->sntcs[i].size; j += 2)
		{
			if (tableWord[ind].cnt == 0)
			{
				ind++;
			}
			text->sntcs[i].words[j] = tableWord[ind].word[tableWord[ind].cnt-1];
			tableWord[ind].cnt--;
		}
	}
	*size = tableSize + 1;
	return tableWord;
}
//aa, aa, bb, bb, bb.
