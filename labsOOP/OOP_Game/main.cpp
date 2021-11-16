#include "GameStart.h"

int main() {
    GameStart::startGameMode("game"); // "game", "features"
    return 0;
}
/*
 * Паттерны 1:
 * 1) Итератор - файл FieldIterator.h
 * 2) Строитель - файл FieldScreen.h
 *
 * Паттерны 2:
 *  1) Стратегия - файл Enemy.h
 *  2) Абстрактная фабрика - файл Field.h
 *  3) Прототип - файл Character.h
 *
 *  Паттерны 3:
 *  1) Адаптер - файл LoggerDataAdapter.hpp
 *  2) Декоратор - файл LoggerDefault.hpp
 *  3) Мост? - файл LoggerDefault.hpp
 *  4) Синглтон - файл LoggerDefault.hpp
 *
 */