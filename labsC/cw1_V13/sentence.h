#include "word.h"
#define SNTC_START_SIZE 2


struct Sentence
{
	Word *words;
	int size;
	int realSize;
};

typedef struct Sentence Sentence;

int initial_sntc(Sentence *new_sntc, int start_size);
int push_back_sntc(Sentence *sntc, Word *word);
int is_equal_sent(Sentence *sent1, Sentence *sent2);
int move_word_n(Sentence *sntc, int n);
void remove_word(Sentence *sntc, int ind);
void rm_word_last_cptlz(Sentence *sntc);
int is_sep_symb(wchar_t c);



