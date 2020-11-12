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
										(size_t) (text->realSize * INCREASE) * sizeof(struct Sentence));
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
		for (int j = i-1; j >= 0; --j)
		{
			if(is_equal_sent(&text->sntcs[i],&text->sntcs[j]))
			{
				remove_sent(text, i);
				break;
			}
		}
	}
}

void remove_sent(struct Text *text, int ind)
{
	for (int i = ind; i < text->realSize-1; ++i)
	{
		text->sntcs[i] = text->sntcs[i + 1];
	}
	free(text->sntcs[text->realSize - 1].words);
	text->size--;
	text->realSize--;
}



//test cases

//abc. abc. abc, eft. abc.@

/*
a. b. a. c.
g. y. z. a, b. c, t. b.@
*/