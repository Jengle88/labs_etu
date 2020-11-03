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
	new_sntc->words = (struct Word **) calloc(new_sntc->realSize, sizeof(struct Word *));
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
		sntc->words[sntc->size++] = word;
		return 1;
	}
	struct Word **tempSntc = (struct Word **) realloc(sntc->words, (size_t) (sntc->realSize * INCREASE * sizeof(struct Word *)));
	if (tempSntc == NULL)
	{
		fprintf(stderr, "%sMemory alloc for sentence failed!%s\n", ERROR_CLR, STD_CLR);
		return -1;
	}
	sntc->words = tempSntc;
	sntc->realSize = (size_t) (sntc->realSize * INCREASE);
	sntc->words[sntc->size++] = word;
	return 1;
}
