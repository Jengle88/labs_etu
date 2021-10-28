#include "FieldScreen.h"

FieldScreen::FieldScreen() {
    field = nullptr;
}

FieldScreen::~FieldScreen() {
    delete field;
}

void FieldScreen::showStartingParamsAndGenerateField(DataManager *dataManager) { // паттерн Builder
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
    srand(time(0));
    field = new Field(height, width, dataManager);
    this->dataManager = dataManager;
    if (field->generateFullField(countWalls)) {
        field->setHeroOnStart();
        field->createHero();
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
    Printer::printFullField(field);
}


bool FieldScreen::registerMovement(char &action, std::string &gameAction) {
    action = getchar();
    std::cin.ignore(32767, '\n');
    CellPoint heroPos = field->getHeroPos();
    thingsManager.tryGenerateThing(field->hero, dataManager); // также считает шаги
    std::pair<bool, Thing> thingOnPos;
    bool status = true;
    switch (tolower(action)) {
        case MoveSide::UP:
            requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1), gameAction);
            return true;
        case MoveSide::DOWN:
            requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1), gameAction);
            return true;
        case MoveSide::LEFT:
            requestMoveHero(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()), gameAction);
            return true;
        case MoveSide::RIGHT:
            requestMoveHero(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()), gameAction);
            return true;
        case MoveSide::FINISH_OUT:
            if (requestMoveOut()) {
                sleep(3);
                action = MoveSide::EXIT;
                return false;
            }
            else
                return true;
        case MoveSide::TAKE:
            requestTakeObject(heroPos);
            return true;
        case MoveSide::FIGHT:
            status = requestStartFight(heroPos);
            if (status == FightStatus::KILLED_HERO) {
                std::cout << "Вы проиграли.\n";
                Printer::printHeroAchievement(field->getHero().getCountKilledEnemy());
                std::cout << "Нажмите любую кнопку, чтобы выйти...\n";
                getchar();
                action = MoveSide::EXIT;
                return false;
            }
            return true;
        case MoveSide::EXIT:
            return false;
        default:
            std::cout << "Команда не распознана.\n";
    }
    return false;
}

void FieldScreen::requestMoveHero(CellPoint from, CellPoint to, std::string &gameAction) {
    if (!field->field.isValidIndexes(to.getX(), to.getY()))
        return;
    if (field->getHeroPos() == from) {
        field->moveHero(to);
    }
    auto thingOnPos = thingsManager.checkCellHasSmth(to);
    if (thingOnPos.first) {
        gameAction = generateTitleForThingAction(thingOnPos.second.getNameThing(), thingOnPos.second.getProperties());
    }
    if (field->getElem(to).getValue().getTypeCell() == TypeCell::FINISH)
        gameAction = "Вы на финишной клетке. Закончить игру? Нажмите q, чтобы выйти.\n";
}

void FieldScreen::requestTakeObject(CellPoint point) {
    auto thingOnPos = thingsManager.checkCellHasSmth(point);
    if (thingOnPos.first) {
        field->getHero().takeThing(thingOnPos.second);
        if (thingOnPos.second.isActiveThing()) {
            field->getHero().resetModel(
                    dataManager->getHero(
                            field->getHero().hasThing(ThingObject::SWORD),
                            field->getHero().hasThing(ThingObject::ARMOR)));
        }
        thingsManager.deleteThingFromField(point);
    }
}

int FieldScreen::requestStartFight(CellPoint point) {
    int statusFight = 1;
    for (int i = -MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; i <= MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; ++i) {
        for (int j = -MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; j <= MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; ++j) {
            if (field->enemies.count(CellPoint(point.getX() + i, point.getY() + j))) {
                system("clear");
                auto fightScreen = FightScreen(this->field->getHero(), this->field->getEnemyFromPoint(
                        CellPoint(point.getX() + i, point.getY() + j)), this->dataManager);
                statusFight = fightScreen.fightObserver();
                if (statusFight == FightStatus::KILLED_ENEMY) {
                    this->field->killEnemy(CellPoint(point.getX() + i, point.getY() + j));
                }
                return statusFight;
            }
        }
    }
    return statusFight;
}

bool FieldScreen::requestMoveOut() const {
    if (field->getElem(field->getHeroPos()).getValue().getTypeCell() == TypeCell::FINISH) {
        Printer::printHeroAchievement(field->getHero().getCountKilledEnemy());
        return true;
    }
    return false;
}

std::string
FieldScreen::generateTitleForThingAction(const std::string &nameThing, const std::map<std::string, double> &properties) {
    std::string res = "На этой клетке лежит " + nameThing + ", который даёт: " +
                      (properties.at("damage") >= 1e-2 ? "Урон: " + std::to_string(
                              round(properties.at("damage") * 100) / 100) + " " : "") +
                      (properties.at("protection") >= 1e-2 ? "Защита: " + std::to_string(
                              round(properties.at("protection") * 100) / 100) + " " : "") +
                      (properties.at("luck") >= 1e-2 ? "Удача: " + std::to_string(
                              round(properties.at("luck") * 100) / 100) + " " : "") +
                      (properties.at("health") >= 1e-2 ? "Здоровье: " + std::to_string(
                              round(properties.at("health") * 100) / 100) + " " : "") +
                      ". Нажмите ";
    res.push_back(MoveSide::TAKE);
    res += ", чтобы взять.";
    return res;
}

void FieldScreen::showStartFieldScreen(DataManager *dataManager) {
    showStartingParamsAndGenerateField(dataManager);
    std::system("clear");
}

void FieldScreen::gameStatusObserver() {
    char action = getchar(); // считываем перенос строки
    std::cout << "Для выхода введите ` и нажмите enter.\n";
    showUpdatedScreen();
    Printer::printInventory(&(this->field->getHero()));
    while (action != MoveSide::EXIT) {
        std::string gameAction = "";
        bool goodMovement = registerMovement(action, gameAction);
        field->moveEnemies();
        if (goodMovement) {
            std::system("clear");
            field->createRandomEnemy();
            std::cout << "Для выхода введите ` и нажмите enter.\n";
            showUpdatedScreen();
            std::cout << gameAction << '\n';
            Printer::printEnemyInfo(&(field->enemies));
            Printer::printInventory(&(this->field->getHero()));
        }
    }
    std::system("clear");
}
