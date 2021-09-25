#include "FieldScreen.h"


FieldScreen::FieldScreen() {
    field = nullptr;
}

void FieldScreen::showStartFieldScreen() {
    showStartingParams();
    std::system("clear");
}

void FieldScreen::showStartingParams() {
    std::cout << "Введите значения параметров:\n";
    bool acceptedParams = false;
    auto enterSizeValue = [](int &val, int height, int width, char title[], bool (*compare_bad)(int, int, int)) {
        while (val < 0) {
            try {
                std::cout << title;
                std::cin >> val;
                if (std::cin.fail())
                    throw 0;
            } catch (int) {
                std::cin.clear();
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
        enterSizeValue(height, height, width, "Высота поля (мин = 2, макс = 1000): ",
                       [](int val, int, int) { return val < 2; });
        enterSizeValue(width, height, width, "Ширина поля (мин = 2, макс = 1000): ",
                       [](int val, int, int) { return val < 2; });
        enterSizeValue(countWalls, height, width,
                       "Количество непроходимых клеток (мин = 2, макс = 1000, макс процент покрытия - 45% от площади поля): ",
                       [](int val, int height, int width) {
                           return (double) val / (width * height) * 100 > PERCENT_WALLS;
                       });
        std::cout << "Значения приняты. Сгенерировать поле? (y - сгенерировать / n - изменить параметры) ";
        char acceptSymbol = getchar(); // считываем лишний символ
        while (true) {
            acceptSymbol = getchar();
            if (acceptSymbol != 'y' && acceptSymbol != 'n') {
                std::cout
                        << "Неверное значение, попробуйте снова. Сгенерировать поле? (y - сгенерировать/n - изменить параметры) ";
            } else break;
        }
        if (acceptSymbol == 'y')
            acceptedParams = true;
    }

    field = new Field(height, width);
    field->generateFullField(countWalls);
    field->setHeroOnStart();
}

void FieldScreen::showUpdatedScreen() const {
    for (int i = 0; i < field->getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
    for (int i = 0; i < field->getHeight(); ++i) {
        std::cout << '|';
        for (int j = 0; j < field->getWidth(); ++j) {
            char c = field->getElem(CellPoint(j, i)).getValue().getCellAsChar();

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

void FieldScreen::gameStatusObserver() {
    auto getch = []()
    {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    };

    char action = '$';
    while (action != '`') {
        registerMovement(action, getch);
        std::system("clear");
        showUpdatedScreen();
    }
}

void FieldScreen::registerMovement(char &action, int (*getch)()) {
    action = getch();
    CellPoint heroPos = field->getHeroPos();
    switch (tolower(action)) {
        case 'w':
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1));
            break;
        case 's':
            requestMoveObject(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1));
            break;
        case 'a':
            requestMoveObject(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()));
            break;
        case 'd':
            requestMoveObject(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()));
            break;
    }
}

void FieldScreen::requestMoveObject(CellPoint from, CellPoint to) {
    if (!field->isValidIndexes(to.getX(), to.getY()))
        return;
    if (field->getHeroPos() == from) {
        field->moveHero(to);
//        field->setElem(from, CellObject(field->getElem(from).getValue().getTypeCell(), TypeObject::NOTHING));
//        field->setElem(to, CellObject(field->getElem(to).getValue().getTypeCell(), TypeObject::HERO));
//        field->heroPos = to;
    }
}


