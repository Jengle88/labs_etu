#pragma once
#include "sentence.h"
#define TEXT_START_SIZE 2
struct Text
{
	struct Sentence **sntcs;
	int size;
	int realSize;
};

int initial_text(struct Text* new_text, int start_size);
int push_back_text(struct Text* text, struct Sentence* sntc);


