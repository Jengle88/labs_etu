#include "text.h"

int main()
{
	struct Word word;
	initial_word(&word,3);
	wchar_t c = L'$';
	while((c = getwchar()) != L'@')
	{
		push_back_word(&word,c);
		wprintf(L"%lc",word.word[word.size-1]);
	}
	struct Sentence sntc;
	initial_sntc(&sntc,2);
	push_back_sntc(&sntc,&word);
	push_back_sntc(&sntc,&word);
	return 0;
	struct Text text;
	initial_text(&text,1);
	push_back_text(&text,&sntc);
	int z = 2;
	return 0;
}