#pragma once

#include "text.h"
#include <stdio.h> //Стандартный однобайтовый ввод-вывод
#include <wchar.h> //"Широкие" многобайтовые символы и их ввод-вывод
#include <wctype.h> //"Классификация" широких символов
#include <locale.h> //Во избежание "крокозяблей" на выводе
#include <stdlib.h>

#define MIN(a, b) (a < b ? a : b)

void out(struct Text text)
{
	for (int i = 0; i < text.size; ++i)
	{
		for (int j = 0; j < text.sntcs[i].size; ++j)
		{
			for (int k = 0; k < text.sntcs[i].words[j].size; ++k)
			{
				wprintf(L"%lc", text.sntcs[i].words[j].word[k]);
			}
			//wprintf(L"\n");
		}
	}
}

void delete_all(struct Text text)
{
	for (int i = 0; i < text.realSize; ++i)
	{
		for (int j = 0; j < text.sntcs[i].realSize; ++j)
		{
			free(text.sntcs[i].words[j].word);
		}
		free(text.sntcs[i].words);
	}
	free(text.sntcs);
}

void print_interface(struct Text text)
{
	wprintf(L"Доступные команды:\n"
			L"1)Сделать сдвиг на N слов вперёд\n"
			L"2)Вывести все уникальные кириллические и латинские символы\n"
			L"3)Посчитать количество слов с длиной 1,2,3...\n"
			L"4)Удалить все слова, заканчивающиеся на заглавный символ\n"
			L"0)Выйти из программы\n"
			L"Введите номер команды...\n");
	int task = 0;
	wscanf(L"%d", &task);
	wchar_t *p = NULL;
	switch (task)
	{
		case 1:
			wprintf(L"Введите номер предложения (1, 2, ...) и смещение:\n");
			int ind, n;
			wscanf(L"%d%d", &ind, &n);
			ind--;
			if (0 <= ind && ind <= text.size - 1 && n >= 0)
			{
				move_word_n(&text.sntcs[ind], n);
				wprintf(L"Выполнено!\n");
				out(text);
			}
			else
				wprintf(L"Неверный индекс или смещение!\n");
			break;
		case 2:
		{
			wchar_t *res = (wchar_t *)malloc(0 * sizeof(wchar_t));
			int size = 0;
			unique_symb(text, &res, &size);
			wprintf(L"Выполнено!\n");
			for (int i = 0; i < size; ++i)
			{
				wprintf(L"%lc ", res[i]);
			}
			break;
		}
		case 3:
		{
			int size = 0;
			int *len_words = unique_len_word(text, &size);
			if (len_words != NULL)
			{
				wprintf(L"Выполнено!\n");
				for (int i = 0; i < size; ++i)
					wprintf(L"%d) %d\n", i + 1, len_words[i]);
			}
			else
				wprintf(L"Не получилось выделить память!\n");
			break;
		}
		case 4:
			//TODO
			break;
		default:
			wprintf(L"Команда не распознана\n");
	}
}


int main()
{
	setlocale(LC_ALL, "");
	struct Text text;
	initial_text(&text, 2);
	wchar_t c = L'$';
	int flag_end_sntc;
	while ((c = getwchar()) != L'@')
	{
		flag_end_sntc = 0;
		struct Sentence sntc;
		initial_sntc(&sntc, 2);
		while (!flag_end_sntc)
		{
			struct Word word;
			//add protect
			initial_word(&word, 3);
			while (c != L' ' && c != L',' && c != L'.')
			{
				//add protect
				push_back_word(&word, c);
				c = getwchar();
			}
			//add protect
			push_back_sntc(&sntc, &word);
			struct Word specWord;
			//add protect
			initial_word(&specWord, 2);
			while (c == L' ' || c == L',' || c == L'.')
			{
				//add protect
				if (c == L'.')
					flag_end_sntc = 1;
				push_back_word(&specWord, c);
				c = getwchar();
			}
			//add protect
			push_back_sntc(&sntc, &specWord);
			if (flag_end_sntc)
			{
				ungetwc(c, stdin);
				push_back_text(&text, &sntc);
			}
		}
	}
	delete_dubl(&text);
	print_interface(text);
	//out(text);
	int z = 2;
	delete_all(text);
	return 0;
}