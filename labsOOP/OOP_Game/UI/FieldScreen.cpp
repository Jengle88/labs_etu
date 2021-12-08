#include "FieldScreen.h"
#include "../Logger/LoggerPull.h"
#include "../KeyControl/KeyControl.h"


std::tuple<int, int, int>
FieldScreen::showStartingParamsAndGenerateField(DataManager *dataManager, KeyControl *keyController) { // паттерн Builder
    std::cout << "Введите значения параметров:\n";
    bool acceptedParams = false;
    auto enterSizeValue = [this, keyController](
            int &val,
            int height,
            int width,
            const char title[],
            bool (*compare_bad)(int, int, int)
    ) {
        while (val < 0) {
            try {
                showMessage(std::string(title));
                val = keyController->requestKeyInt();
            } catch (std::invalid_argument) {
                showMessage("Введённое значение неверно.\n");
                keyController->clearInputState();
                keyController->requestTrashIgnore();
                val = -1;
                continue;
            }
            if (compare_bad(val, height, width)) {
                showMessage("Введённое значение неверно.\n");
                keyController->clearInputState();
                keyController->requestTrashIgnore();
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

        std::string message = "Значения приняты. Сгенерировать поле? (";
        message.push_back(keyController->getKey(getScreenName(), HeroKeysControl::FIELD_ACCEPT_GENERATE));
        message += " - сгенерировать / ";
        message.push_back(keyController->getKey(getScreenName(), HeroKeysControl::FIELD_CANCEL_GENERATE));
        message += " - изменить параметры) ";
        showMessage(message);
        int willGenerate = '#';
        keyController->requestTrashIgnore(); // считываем лишний символ после ввода числа непроходимых клеток
        while (true) {
            willGenerate = keyController->requestKeyAction(getScreenName());
            if (willGenerate != HeroKeysControl::FIELD_ACCEPT_GENERATE && willGenerate != HeroKeysControl::FIELD_CANCEL_GENERATE) {
                std::string message = "Неверное значение, попробуйте снова. Сгенерировать поле? (";
                message.push_back(keyController->getKey(getScreenName(), HeroKeysControl::FIELD_ACCEPT_GENERATE));
                message += " - сгенерировать / ";
                message.push_back(keyController->getKey(getScreenName(), HeroKeysControl::FIELD_CANCEL_GENERATE));
                message += " - изменить параметры) ";
                showMessage(message);
                keyController->requestTrashIgnore();
            } else break;
        }
        if (willGenerate == HeroKeysControl::FIELD_ACCEPT_GENERATE)
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

std::tuple<int, int, int> FieldScreen::showStartFieldScreen(DataManager *dataManager, KeyControl *keyController) {
    auto res = showStartingParamsAndGenerateField(dataManager, keyController);
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

std::string FieldScreen::getScreenName() const {
    return "fieldScreen";
}
