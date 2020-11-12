#include "text.h"

int initial_text(struct Text *new_text, int start_size)
{
	if (start_size < 0)
	{
		fprintf(stderr, "%sError, bad start_size for new_text%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	new_text->size = 0;
	new_text->realSize = MAX(start_size, TEXT_START_SIZE);
	new_text->sntcs = (struct Sentence *) calloc(new_text->realSize, sizeof(struct Sentence));
	if (new_text->sntcs == NULL)
	{
		fprintf(stderr, "%sMemory alloc for text failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	return 1;
}

int push_back_text(struct Text *text, struct Sentence *sntc)
{
	if (text->size + 1 < text->realSize)
	{
		text->sntcs[text->size++] = *sntc;
		return 1;
	}
	struct Sentence *tempText = (struct Sentence *) realloc(text->sntcs,
															(size_t) (text->realSize * INCREASE) *
															sizeof(struct Sentence));
	if (tempText == NULL)
	{
		fprintf(stderr, "%sMemory alloc for text failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	text->sntcs = tempText;
	text->realSize = (size_t) (text->realSize * INCREASE);
	text->sntcs[text->size++] = *sntc;
	return 1;
}

void delete_dubl(struct Text *text)
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

void remove_sent(struct Text *text, int ind)
{
	for (int i = ind; i < text->realSize - 1; ++i)
	{
		text->sntcs[i] = text->sntcs[i + 1];
	}
	free(text->sntcs[text->realSize - 1].words);
	text->size--;
	text->realSize--;
}


void unique_symb(struct Text text, wchar_t **res, int *n)
{
	int tableCntOfENSymb[L'z' - L'a' + 1] = {0};
	int tableCntOfRUSymb[L'я' - L'а' + 1] = {0};
	int size = 0;
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
	//исправить под использование res
	wchar_t *resTemp = (wchar_t *) malloc(size * sizeof(wchar_t));
	int ind = 0;
	for (int i = 0; i < L'я' - L'а' + 1; ++i)
	{
		if (tableCntOfRUSymb[i] > 0)
			resTemp[ind++] = L'а' + i;
	}
	for (int i = 0; i < L'z' - L'a' + 1; ++i)
	{
		if (tableCntOfENSymb[i] > 0)
			resTemp[ind++] = L'a' + i;
	}
	*res = resTemp;
	*n = size;
}

int *unique_len_word(struct Text text, int *size)
{
	int maxSize = -1;
	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (text.sntcs[i].words[j].word[0] != '.' && text.sntcs[i].words[j].word[0] != ',' &&
				text.sntcs[i].words[j].word[0] != ' ')
			{
				maxSize = MAX(maxSize,text.sntcs[i].words[j].size);
			}
		}
	}
	int *res = (int *) calloc(maxSize, sizeof(int));

	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			if (text.sntcs[i].words[j].word[0] != '.' && text.sntcs[i].words[j].word[0] != ',' &&
				text.sntcs[i].words[j].word[0] != ' ')
			{
				res[text.sntcs[i].words[j].size - 1]++;
			}
		}
	}
	*size = maxSize;
	return res;
}




//test cases

//abc. abc. abc, eft. abc.@

/*
a. b. a. c.
g. y. z. a, b. c, t. b.@
*/