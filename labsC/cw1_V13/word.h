#include <wchar.h>
#include <wctype.h> //"Классификация" широких символов
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#define ERROR_CLR   "\033[0;31m"
#define STD_CLR   "\033[0m"
#define MAX(a,b) (a > b ? a : b)
#define INCREASE 1.6

#define WORD_START_SIZE 4

#define SOME_ERROR 0
#define ALL_OK 1

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



//Когда-то на территории Новокузнецка жили старинные народы, шорцы и абинцы. Их называли татарами-кузнецами, за умение хорошо работать с металлом.
//А крепость, которая выросла на месте их поселений, стала Кузнецким острогом. И, наконец, из острога появился город Новокузнецк.
//А недалеко от города, один из лучших горнолыжных курортов России. Utair приглашает посетить Новокузнецк зимой.@
//
//
//
//0        1 2  3 4          5 6            7 8    9 10       11 12     13 14   15 16 17 18     19
//|Когда-то| |на| |территории| |Новокузнецка| |жили| |старинные| |народы|, |шорцы|  |и|  |абинцы|.|
//|жили| |старинные| |народы|, |шорцы|  |и|  |абинцы| |Когда-то| |на| |территории| |Новокузнецка|
