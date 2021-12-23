#include "GameStart.h"

int main() {
    GameStart::startGameMode();
    return 0;
}
/*
 * Паттерны 1:
 * 1) Итератор - файл FieldIterator.h
 * 2) Строитель - файл FieldScreen.h
 *
 * Паттерны 2:
 *  1) Прототип - файл Character.h
 *
 *  Паттерны 3:
 *  1) Адаптер - файл LoggerDataAdapter.h
 *  2) Синглтон - файл LoggerPull.h
 *
 */