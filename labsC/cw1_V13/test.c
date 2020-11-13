#pragma once

#include "text.h"
#include <stdio.h> //Стандартный однобайтовый ввод-вывод
#include <wchar.h> //"Широкие" многобайтовые символы и их ввод-вывод
#include <wctype.h> //"Классификация" широких символов
#include <locale.h> //Во избежание "крокозяблей" на выводе
#include <stdlib.h>

/* TODO list:
 * 1)добавить в строки \0
 * 2)заменить в unique_symb resTemp на res ----------- V
 * 3)проверить на большем количестве тестов
 * 4)улучшить структуризацию функций в файлах
 * 5)избавить код от мусора
 * 6)проверить функции на предмет "утечки памяти" ---- V
 * 7)перевести вывод ошибок на русский язык	---------- V
 * 8)добавить выход при ошибке выделения памяти ------ V
 * 9)заменить @ на ввод из терминала
*/


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

void do_task(struct Text text)
{
	int task = 0;
	wscanf(L"%d", &task);
	switch (task)
	{
		case 1:
		{
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
		}
		case 2:
		{
			wchar_t *res;
			int size = 0;
			res = unique_symb(text, &size);
			wprintf(L"Выполнено!\n");
			for (int i = 0; i < size; ++i)
			{
				wprintf(L"%lc ", res[i]);
			}
			free(res);
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
				free(len_words);
			}
			else
				wprintf(L"Не получилось выделить память!\n");
			break;
		}
		case 4:
		{
			for (int i = 0; i < text.size; ++i)
			{
				rm_word_last_cptlz(&text.sntcs[i]);
			}
			wprintf(L"Выполнено!\n");
			out(text);
			break;
		}
		case 0:
			wprintf(L"Работа завершена!\n");
			return;
		default:
			wprintf(L"Команда не распознана\n");
	}
}


int main()
{
	setlocale(LC_ALL, "");
	struct Text text;
	if(!initial_text(&text, 2))
		return -1;
	fill_text_fr_inp(&text);
	delete_dubl(&text);
	wprintf(L"Доступные команды:\n"
			L"1)Сделать сдвиг на N слов вперёд\n"
			L"2)Вывести все уникальные кириллические и латинские символы\n"
			L"3)Посчитать количество слов с длиной 1,2,3...\n"
			L"4)Удалить все слова, заканчивающиеся на заглавный символ\n"
			L"0)Выйти из программы\n"
			L"Введите номер команды...\n");
	do_task(text);
	delete_all(text);
	return 0;
}