#include "sentence.h"

int initial_sntc(struct Sentence *new_sntc, int start_size)
{
	if (start_size < 0)
	{
		fprintf(stderr, "%sError, bad start_size for sentence%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	new_sntc->size = 0;
	new_sntc->realSize = MAX(start_size, SNTC_START_SIZE);
	new_sntc->words = (struct Word *) calloc(new_sntc->realSize, sizeof(struct Word));
	if (new_sntc->words == NULL)
	{
		fprintf(stderr, "%sMemory alloc for sentence failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	return 1;
}

int push_back_sntc(struct Sentence *sntc, struct Word *word)
{
	if (sntc->size + 1 < sntc->realSize)
	{
		sntc->words[sntc->size++] = *word;
		return 1;
	}
	struct Word *tempSntc = (struct Word *) realloc(sntc->words,
													(size_t)(sntc->realSize * INCREASE) * sizeof(struct Word));
	if (tempSntc == NULL)
	{
		fprintf(stderr, "%sMemory alloc for sentence failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	sntc->words = tempSntc;
	sntc->realSize = (size_t) (sntc->realSize * INCREASE);
	sntc->words[sntc->size++] = *word;
	return 1;
}

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

int is_equal_sent(struct Sentence *sent1, struct Sentence *sent2)
{
	if (sent1->size != sent2->size)
		return 0;
	for (int i = 0; i < sent1->size; ++i)
	{
		for (int j = 0; j < sent1->words[i].size; ++j)
		{
			if (towlower(sent1->words[i].word[j]) != towlower(sent2->words[i].word[j]))
				return 0;
		}
	}
	return 1;
}

void move_word_n(struct Sentence *sntc, int n)
{
	int ind = sntc->size - 2;
	n %= (sntc->size / 2);
	struct Word tempWord = sntc->words[ind];
	do
	{
		sntc->words[ind] = sntc->words[(sntc->size + ind - 2 * n) % sntc->size];
		ind = (sntc->size + ind - 2 * n) % sntc->size;
	} while((sntc->size + ind - 2 * n) % sntc->size != sntc->size - 2);
	sntc->words[ind] = tempWord;
}

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
				{
					push_back_word(&sntc->words[i-1],sntc->words[i].word[j]);
				}
				remove_word(sntc,i);
			}
		}
	}
}


//a, b, c. A1, B2, C3.@