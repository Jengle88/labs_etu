#include "Printer.h"

void Printer::printFullField(Field *field) {
    for (int i = 0; i < field->getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
    auto fieldIterator = field->getFieldIterator();
    for (int i = 0; i < field->getHeight(); ++i) {
        std::cout << '|';
        for (int j = 0; j < field->getWidth(); ++j) {
            char c = (fieldIterator++).getElem().getValue().getCellAsChar();
            std::cout << (c == '#' ? ' ' : c);
        }
        std::cout << '|';
        std::cout << '\n';
    }
    for (int i = 0; i < field->getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
}

void Printer::printInventory(MainHero *hero, bool withSerialNumber) {
    auto inventory = hero->getInventory();
    std::cout << "Инвентарь: \n";
    if (inventory.empty()) {
        std::cout << "(Пустой)\n\n";
        return;
    }
    for (int i = 0; i < inventory.size(); ++i) {
        if (withSerialNumber)
            std::cout << i+1 << ") ";
        std::cout << inventory[i].getNameThing() << '\n';
    }
    std::cout << '\n';
}

void Printer::printEnemyInfo(std::map<CellPoint, Enemy *> *enemies) {
    int cntMonster = 0, cntArcher = 0, cntGargoyle = 0; // Не очень оптимизировано
    for (const auto &enemy: *enemies) {
        switch (enemy.second->getCharacterType()) {
            case CharacterType::MONSTER:
                cntMonster++;
                break;
            case CharacterType::SKELETON_ARCHER:
                cntArcher++;
                break;
            case CharacterType::GARGOYLE:
                cntGargoyle++;
                break;
        }
    }
    std::cout << "Сейчас на поле: \n"
                 "Монстр: " + std::to_string(cntMonster) + ",\n"
                 "Скелет-лучник: " + std::to_string(cntArcher) + ",\n"
                 "Горгулья: " + std::to_string(cntGargoyle) + "\n\n";
}

void Printer::printFight(const DataManager &dataManager, const MainHero &hero, const Enemy &enemy) {
    auto heroHead = dataManager.getModelHeroHead();

}
