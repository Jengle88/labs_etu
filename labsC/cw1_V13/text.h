#include "sentence.h"
#define TEXT_START_SIZE 2

struct Text
{
	struct Sentence *sntcs;
	int size;
	int realSize;
};

int initial_text(struct Text* new_text, int start_size);
int push_back_text(struct Text* text, struct Sentence* sntc);
void remove_sent(struct Text* text, int ind);
void delete_dubl(struct Text* text);
wchar_t* unique_symb(struct Text text, int *n);
int *unique_len_word(struct Text text, int *size);
int fill_text_fr_inp(struct Text* text);