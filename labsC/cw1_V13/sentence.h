#include "word.h"
#define SNTC_START_SIZE 2 //начальный размер памяти для предложения


struct Sentence
{
	Word *words;
	int size;
	int realSize;
};

typedef struct Sentence Sentence;

int initial_sntc(Sentence *new_sntc, int start_size);
int push_back_sntc(Sentence *sntc, Word *word);
int is_equal_sntc(Sentence *sntc1, Sentence *sntc2);
void remove_word(Sentence *sntc, int ind);
void swap_sntc(Sentence *sntc1, Sentence *sntc2);
int move_word_n(Sentence *sntc, int n);
void rm_word_last_cptlz(Sentence *sntc);
