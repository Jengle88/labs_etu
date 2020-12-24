#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#define ERROR_CLR   "\033[0;31m"
#define STD_CLR   "\033[0m"
#define MAX(a,b) (a > b ? a : b)

#define INCREASE 1.6 //коэффициент для увеличения памяти
#define WORD_START_SIZE 4 //начальный размер памяти для слова

//коды ошибок
#define SOME_ERROR 0
#define ALL_OK 1

//варианты равенства
#define NOT_EQUAL 0
#define EQUAL 1

struct Word
{
	wchar_t *word;
	int size;
	int realSize;
};



typedef struct Word Word;

int initial_word(Word* new_word, int start_size);
int push_back_word(Word* word, wchar_t c);
int is_equal_word(Word* word1, Word* word2);
void swap_word(Word* word1, Word* word2);
int is_sep_symb(wchar_t c);
