#pragma once

#include "text.h"
#include <stdio.h> //Стандартный однобайтовый ввод-вывод
#include <wchar.h> //"Широкие" многобайтовые символы и их ввод-вывод
#include <locale.h> //Для подключения правильной локализации

/* TODO list:
 * 1)проверить на большем количестве тестов
 * 2)улучшить структуризацию функций в файлах
 * 3)избавить код от мусора
 * 4)заменить @ на ввод из терминала
 * 5)исправить free в delete_all --------------------------- V
 * 6)исправить смещение ------------------------------------ V
*/

int do_task(Text *text);


#define EXIT 0
#define WORKING 1

enum EXITS
{
	GOOD_EXIT,
	BAD_EXIT
};

enum TASKS
{
	MOVE_WORD = 1,
	UNIQ_SYMB,//заполняются последовательно
	CNT_WORD_WITH_LEN,
	RM_WORD_LAST_CAPIT,
	OUT_TEXT,
	CLEAR_TERM,
	STOP_WORK = 0,
};

int main()
{
	setlocale(LC_ALL, "");
	Text text;
	wprintf(L"Введите текст(два переноса строки являются признаком конца ввода текста)\n");
	if (!initial_text(&text, 2) || !input_text(&text))
	{
		fwprintf(stderr, L"%Ошибка выделения памяти при исполнении функции!!%s\n", ERROR_CLR, STD_CLR);
		return BAD_EXIT;
	}
	delete_dubl(&text);
	int working = 1;
	while (working)
	{
		wprintf(L"Доступные команды:\n"
				L"1)Сделать сдвиг на N слов вперёд\n"
				L"2)Вывести все уникальные кириллические и латинские символы\n"
				L"3)Посчитать количество слов с длиной 1,2,3...\n"
				L"4)Удалить все слова, заканчивающиеся на заглавный символ\n"
				L"5)Вывести текст\n"
				L"6)Очистить терминал\n"
				L"0)Выйти из программы\n"
				L"Введите номер команды...\n");
		working = do_task(&text);
	}
	delete_all(&text);
	return GOOD_EXIT;
}

//выполнить опцию
int do_task(Text *text)
{
	int task = 0;
	wscanf(L"%d", &task);
	switch (task)
	{
		case MOVE_WORD:
		{
			wprintf(L"Введите номер предложения (1, 2, ...) и смещение:\n");
			int ind, n;
			wscanf(L"%d%d", &ind, &n);
			ind--;
			if (0 <= ind && ind <= text->size - 1 && n >= 0)
			{
				if(move_word_n(&text->sntcs[ind], n) == ALL_OK)
					wprintf(L"Выполнено!\n");
				else
					fwprintf(stderr, L"%sОшибка памяти при исполнении функции!!%s\n", ERROR_CLR, STD_CLR);
			}
			else
				wprintf(L"%sНеверный индекс или смещение!%s\n", ERROR_CLR, STD_CLR);
			break;
		}
		case UNIQ_SYMB:
		{
			wchar_t *res;
			int size = 0;
			res = unique_symb(*text, &size);
			if (res != NULL)
			{
				wprintf(L"Выполнено!\n");
				for (int i = 0; i < size; ++i)
				{
					wprintf(L"%lc ", res[i]);
				}
				wprintf(L"\n");
				free(res);
			}
			else
				fwprintf(stderr, L"%sНе получилось выделить память!!%s\n", ERROR_CLR, STD_CLR);
			break;
		}
		case CNT_WORD_WITH_LEN:
		{
			int size = 0;
			int *len_words = unique_len_word(*text, &size);
			if (len_words != NULL)
			{
				wprintf(L"Выполнено!\n");
				for (int i = 0; i < size; ++i)
					wprintf(L"%d) %d\n", i + 1, len_words[i]);
				free(len_words);
			}
			else
				fwprintf(stderr, L"%sНе получилось выделить память!!%s\n", ERROR_CLR, STD_CLR);
			break;
		}
		case RM_WORD_LAST_CAPIT:
		{
			for (int i = 0; i < text->size; ++i)
			{
				rm_word_last_cptlz(&(text->sntcs[i]));
			}
			wprintf(L"Выполнено!\n");
			break;
		}
		case OUT_TEXT:
		{
			print_text(text);
			wprintf(L"\n");
			break;
		}
		case CLEAR_TERM:
		{
			system("clear");
			break;
		}
		case STOP_WORK:
		{
			wprintf(L"Работа завершена!\n");
			return EXIT;
		}
		default:
			wprintf(L"%sКоманда не распознана!%s\n", ERROR_CLR, STD_CLR);
	}
	return WORKING;
}



