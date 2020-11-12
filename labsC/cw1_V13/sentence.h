#include "word.h"
#define SNTC_START_SIZE 2

struct Sentence
{
	struct Word *words;
	int size;
	int realSize;
};

int initial_sntc(struct Sentence* new_sntc, int start_size);
int push_back_sntc(struct Sentence *sntc, struct Word *word);
int is_equal_sent(struct Sentence *sent1, struct Sentence *sent2);
void move_word_n(struct Sentence *sntc, int n);
void remove_word(struct Sentence *sntc, int ind);
void rm_word_last_cptlz(struct Sentence *sntc);



