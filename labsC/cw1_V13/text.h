#include "sentence.h"
#define TEXT_START_SIZE 2

struct Text
{
	Sentence *sntcs;
	int size;
	int realSize;
};

typedef struct Text Text;

int initial_text(Text* new_text, int start_size);
int push_back_text(Text* text, Sentence* sntc);
void remove_sent(Text* text, int ind);
void delete_dubl(Text* text);
void delete_all(Text *text);
wchar_t* unique_symb(Text text, int *n);
int *unique_len_word(Text text, int *size);
int input_text(Text* text);
void print_text(Text *text);
