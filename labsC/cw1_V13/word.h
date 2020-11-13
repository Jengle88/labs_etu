#include <wchar.h>
#include <wctype.h> //"Классификация" широких символов
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
#define ERROR_CLR   "\033[0;31m"
#define STD_CLR   "\033[0m"
#define INCREASE 1.6
#define WORD_START_SIZE 2
#define MAX(a,b) (a > b ? a : b)

struct Word
{
	wchar_t *word;
	int size;
	int realSize;
};

int initial_word(struct Word* new_word, int start_size);
int push_back_word(struct Word* word, wchar_t c);