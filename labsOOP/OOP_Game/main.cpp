#include "GameStart.h"

int main() {
    GameStart::startGameMode("game"); // "game", "features"
    return 0;
}
/*
 * Паттерны:
 *  1) Стратегия - файл Enemy.h
 *  2) Абстрактная фабрика - файл Field.h
 *  3) Прототип - файл Character.h
 */