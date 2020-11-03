#include "text.h"

int main()
{
	struct Word word;
	initial_word(&word,3);
	push_back_word(&word,L'А');
	push_back_word(&word,L'Б');
	push_back_word(&word,L'В');
	struct Sentence sntc;
	initial_sntc(&sntc,2);
	push_back_sntc(&sntc,&word);
	push_back_sntc(&sntc,&word);
	struct Text text;
	initial_text(&text,1);
	push_back_text(&text,&sntc);
	int z = 2;
	return 0;
}