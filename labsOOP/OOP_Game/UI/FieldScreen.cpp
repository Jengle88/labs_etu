#include "FieldScreen.h"


FieldScreen::FieldScreen() {
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
        enterSizeValue(height, height, width, ("Высота поля (мин = " + std::to_string(DOWN_LIMIT_HEIGHT) + ", макс = " + std::to_string(UP_LIMIT_HEIGHT) + "): ").c_str(),
                       [](int val, int, int) { return !Grid::isValidHeight(val); });
        enterSizeValue(width, height, width, ("Ширина поля (мин = " + std::to_string(DOWN_LIMIT_WIDTH) + ", макс = " + std::to_string(UP_LIMIT_WIDTH) +"): ").c_str(),
                       [](int val, int, int) { return !Grid::isValidWidth(val); });
        enterSizeValue(countWalls, height, width,
                       ("Количество непроходимых клеток (макс процент покрытия - " + std::to_string(PERCENT_WALLS) + "% от площади поля): ").c_str(),
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
    if(field->generateFullField(countWalls))
        field->setHeroOnStart();
    else {
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

bool FieldScreen::registerMovement(char &action) {
    action = getchar();
    std::cin.ignore(32767, '\n');
    CellPoint heroPos = field->getHeroPos();
    switch (tolower(action)) {
        case MoveSide::UP:
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1));
            return true;
        case MoveSide::DOWN:
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1));
            return true;
        case MoveSide::LEFT:
            requestMoveObject(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()));
            return true;
        case MoveSide::RIGHT:
            requestMoveObject(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()));
            return true;
        case MoveSide::EXIT:
            return false;
        default:
            std::cout << "Команда не распознана.\n";
    }
    return false;
}

void FieldScreen::requestMoveObject(CellPoint from, CellPoint to) {
    if (!field->field.isValidIndexes(to.getX(), to.getY()))
        return;
    if (field->getHeroPos() == from) {
        field->moveHero(to);
    }
}

void FieldScreen::showStartFieldScreen() {
    showStartingParams();
    std::system("clear");
}

void FieldScreen::gameStatusObserver() {
    char action = getchar(); // считываем перенос строки
    std::cout << "Для выхода введите ` и нажмите enter.\n";
    showUpdatedScreen();
    while (action != MoveSide::EXIT) {
        bool goodMovement = registerMovement(action);
        if (goodMovement) {
            std::system("clear");
            std::cout << "Для выхода введите ` и нажмите enter.\n";
            showUpdatedScreen();
        }
    }
    std::system("clear");
}
