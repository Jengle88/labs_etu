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
            std::cout << i + 1 << ") ";
        std::cout << inventory[i].getNameThing() << '\n';
    }
    std::cout << '\n';
}

void Printer::printEnemyInfo(std::map<CellPoint, Enemy *> *enemies) {
    int cntMonster = 0, cntArcher = 0, cntGargoyle = 0; // Не очень оптимизировано
    for (const auto &enemy: *enemies) {
        if (enemy.second->getName() == "Monster") {
            cntMonster++;
        } else if (enemy.second->getName() == "Archer") {
            cntArcher++;
        } else if (enemy.second->getName() == "Gargoyle") {
            cntGargoyle++;
        }
    }
    std::cout << "Сейчас на поле: \n"
                 "Монстр: " + std::to_string(cntMonster) + ",\n"
                 "Скелет-лучник: " + std::to_string(cntArcher) + ",\n"
                 "Горгулья: " + std::to_string(cntGargoyle) + "\n\n";
}

void Printer::printHealthInfo(double heroHealth, double enemyHealth) {
    std::cout << "HP: " << heroHealth << "\t\t\t" << "HP: " << enemyHealth << '\n';
}

void Printer::printAttackInfo(std::string nameCharacter, double damage, bool wasDodge, bool wasCritical) {
    std::cout << "Персонаж " << nameCharacter << " нанёс " << damage << " урона, " <<
              (wasDodge ? "совершил уклонение, " : "не совершил уклонение, ") <<
              (wasCritical ? "нанёс критический урон.\n" : "не нанёс критический урон.\n");
}

void Printer::printHeroAchievement(std::map<std::string, int> &achievement) {
    std::cout << "Вы убили " << achievement["Monster"] << " монстров.\n";
    std::cout << "Вы убили " << achievement["Archer"] << " скелетов-лучников.\n";
    std::cout << "Вы убили " << achievement["Gargoyle"] << " горгулий.\n";
}

