#pragma once
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "word.h"
#define SNTC_START_SIZE 2

struct Sentence
{
	struct Word **words;
	int size;
	int realSize;
};

int initial_sntc(struct Sentence* new_sntc, int start_size);
int push_back_sntc(struct Sentence *sntc, struct Word *word);




