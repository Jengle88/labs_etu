#include <termios.h>
#include <unistd.h>
#include "FieldScreen.h"


FieldScreen::FieldScreen() : thingsManager(field) {
    field = nullptr;
}

void FieldScreen::showStartingParams() { // паттерн Builder
    std::cout << "Введите значения параметров:\n";
    bool acceptedParams = false;
    auto enterSizeValue = [](
            int &val,
            int height,
            int width,
            const char title[],
            bool (*compare_bad)(int, int, int)
    ) {
        while (val < 0) {
            try {
                std::cout << title;
                std::cin >> val;
                if (std::cin.fail())
                    throw -1;
            } catch (int) {
                std::cin.clear(); // убирает флаг fail с cin
                std::cin.ignore(32767, '\n');
                std::cout << "Введённое значение неверно.\n";
                val = -1;
                continue;
            }
            if (compare_bad(val, height, width)) {
                std::cout << "Введённое значение неверно.\n";
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                val = -1;
            }
        }
    };
    int height, width, countWalls;
    while (!acceptedParams) {
        height = width = countWalls = -1;
        enterSizeValue(height, height, width, ("Высота поля (мин = " + std::to_string(DOWN_LIMIT_HEIGHT) + ", макс = " +
                                               std::to_string(UP_LIMIT_HEIGHT) + "): ").c_str(),
                       [](int val, int, int) { return !Grid::isValidHeight(val); });
        enterSizeValue(width, height, width, ("Ширина поля (мин = " + std::to_string(DOWN_LIMIT_WIDTH) + ", макс = " +
                                              std::to_string(UP_LIMIT_WIDTH) + "): ").c_str(),
                       [](int val, int, int) { return !Grid::isValidWidth(val); });
        enterSizeValue(countWalls, height, width,
                       ("Количество непроходимых клеток (макс процент покрытия - " + std::to_string(PERCENT_WALLS) +
                        "% от площади поля): ").c_str(),
                       [](int val, int height, int width) {
                           return (double) val / (width * height) * 100 > PERCENT_WALLS;
                       });
        std::cout << "Значения приняты. Сгенерировать поле? (y - сгенерировать / n - изменить параметры) ";
        char acceptSymbol = getchar(); // считываем лишний символ после ввода числа непроходимых клеток
        while (true) {
            acceptSymbol = getchar();
            if (acceptSymbol != 'y' && acceptSymbol != 'n') {
                std::cout
                        << "Неверное значение, попробуйте снова. Сгенерировать поле? (y - сгенерировать/n - изменить параметры) ";
                std::cin.ignore(32767, '\n');
            } else break;
        }
        if (acceptSymbol == 'y')
            acceptedParams = true;
    }
    field = new Field(height, width);
    if (field->generateFullField(countWalls)) {
        field->setHeroOnStart();
        field->createHero(CHARACTER_MAX_HEALTH, 0, 0, 1);
        thingsManager = ThingsManager(field);
    } else {
        std::cout << "Не удалось сгенерировать поле!\n";
        throw -1;
    }
}

void FieldScreen::showUpdatedScreen() const {
    if (!this->field->getStatusStartFinish() || !this->field->getStatusWay()) {
        throw -1;
    }

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

/*
char getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
 */

bool FieldScreen::registerMovement(char &action, std::string &gameAction) {
//    action = getch();
    action = getchar();
    std::cin.ignore(32767, '\n');
    CellPoint heroPos = field->getHeroPos();
    thingsManager.tryGenerateThing(field->hero); // считает шаги
    std::pair<bool, Thing> thingOnPos;
    switch (tolower(action)) {
        case MoveSide::UP:
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1), gameAction);
            return true;
        case MoveSide::DOWN:
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1), gameAction);
            return true;
        case MoveSide::LEFT:
            requestMoveObject(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()), gameAction);
            return true;
        case MoveSide::RIGHT:
            requestMoveObject(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()), gameAction);
            return true;
        case MoveSide::TAKE:
            requestTakeObject(heroPos);
            return true;
        case MoveSide::EXIT:
            return false;
        default:
            std::cout << "Команда не распознана.\n";
    }
    return false;
}

void FieldScreen::requestMoveObject(CellPoint from, CellPoint to, std::string& gameAction) {
    if (!field->field.isValidIndexes(to.getX(), to.getY()))
        return;
    if (field->getHeroPos() == from) {
        field->moveHero(to);
    }
    auto thingOnPos = thingsManager.checkCell(to);
    if (thingOnPos.first) {
        gameAction = generateTitleForThingAction(thingOnPos.second.getNameThing(), thingOnPos.second.getProperties());
    }
}

void FieldScreen::showStartFieldScreen() {
    showStartingParams();
    std::system("clear");
}

void FieldScreen::gameStatusObserver() {
    char action = getchar(); // считываем перенос строки
//    char action = getch(); // считываем перенос строки
    std::cout << "Для выхода введите ` и нажмите enter.\n";
    field->createMonster(MONSTER_MAX_HEALTH, 1, 1);
    showUpdatedScreen();
    printInventory();
    while (action != MoveSide::EXIT) {
        std::string gameAction = "";
        bool goodMovement = registerMovement(action, gameAction);
        if (goodMovement) {
            std::system("clear");
            std::cout << "Для выхода введите ` и нажмите enter.\n";
            field->moveEnemies();
            showUpdatedScreen();
            std::cout << gameAction << '\n';
            printInventory();
        }
    }
    std::system("clear");
}

FieldScreen::~FieldScreen() {
    delete field;
}

std::string
FieldScreen::generateTitleForThingAction(const std::string &nameThing, const std::vector<double> &properties) {
    std::string res = "На этой клетке лежит " + nameThing + ", который даёт: " +
           (properties[0] >= 1e-2 ? "Урон: " + std::to_string(round(properties[0] * 100) / 100) + " " : "") +
           (properties[1] >= 1e-2 ? "Защита: " + std::to_string(round(properties[1] * 100) / 100) + " " : "") +
//           (properties[2] >= 1e-2 ? "Выносливость: " + std::to_string(round(properties[2] * 100) / 100) + " " : "") +
           (properties[3] >= 1e-2 ? "Удача: " + std::to_string(round(properties[3] * 100) / 100) + " " : "") +
           (properties[4] >= 1e-2 ? "Здоровье: " + std::to_string(round(properties[4] * 100) / 100) + " " : "") +
           ". Нажмите ";
    res.push_back(MoveSide::TAKE);
    res += ", чтобы взять.";
    return res;
}

void FieldScreen::printInventory() const {
    auto inventory = this->field->getHero().getInventory();
    std::cout << "Инвентарь: \n";
    if (inventory.empty()) {
        std::cout << "(Пустой)\n\n";
        return;
    }
    for(const auto& thing : inventory) {
        std::cout << thing.getNameThing() << '\n';
    }
    std::cout << '\n';
}

void FieldScreen::requestTakeObject(CellPoint point) {
    auto thingOnPos = thingsManager.checkCell(point);
    if (thingOnPos.first) {
        field->getHero().takeThing(thingOnPos.second);
        thingsManager.deleteThingFromField(point);
    }
}
