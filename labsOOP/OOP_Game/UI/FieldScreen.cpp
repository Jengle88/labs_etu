#include "FieldScreen.h"
#include "../Logger/LoggerPull.h"


std::tuple<int, int, int> FieldScreen::showStartingParamsAndGenerateField(DataManager *dataManager) { // паттерн Builder
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
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<int>(height, "Высота поля"));
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<int>(width, "Ширина поля"));
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<int>(countWalls, "Количество непроходимых клеток поля"));
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
    return { height, width, countWalls };
}

void FieldScreen::showUpdatedScreen(Field *field) const {
    if (!field->getStatusStartFinish() || !field->getStatusWay()) {
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Попытка отобразить не до конца сгенерированное поле"), LoggerPull::LoggingType::Error);
        throw std::logic_error("Попытка отобразить не до конца сгенерированное поле");
    }
    Printer::printFullField(field);
}

std::string
FieldScreen::createTitleForThingAction(const std::string &nameThing, const std::map<std::string, double> &properties,
                                       char takeKey) {
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
    res.push_back(takeKey);
    res += ", чтобы взять.";
    return res;
}

std::tuple<int, int, int> FieldScreen::showStartFieldScreen(DataManager *dataManager) {
    auto res = showStartingParamsAndGenerateField(dataManager);
    clearScreen();
    return res;
}

void FieldScreen::showMessage(const std::string &message) const {
    Printer::printMessage(message);
}

void FieldScreen::showEnemyInfo(std::map<CellPoint, Enemy *> *enemies) const {
    Printer::printEnemyInfo(enemies);
}

void FieldScreen::showInventory(MainHero *hero, bool withSerialNumber) const {
    Printer::printInventory(hero, withSerialNumber);
}

void FieldScreen::clearScreen() const {
    std::system("clear");
}

void FieldScreen::showHeroAchievement(std::map<std::basic_string<char>, int> &achievement) const {
    Printer::printHeroAchievement(achievement);
}
