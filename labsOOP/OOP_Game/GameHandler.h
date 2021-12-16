#pragma once

#include "Rules/DifficultPreset.h"
#include "Data/DataManager.h"
#include "UI/FieldScreen.h"
#include "Logger/LoggerDataAdapter.h"
#include "Logger/LoggerPull.h"
#include "Rules/RulesChecker.h"
#include "UI/StartScreen.h"
#include "KeyControl/KeyControl.h"
#include "UI/KeySettingsScreen.h"

enum FightStatus {
    LEAVE_FIGHT = -1,
    KILLED_ENEMY = 1,
    KILLED_HERO = 0
};

template<KeyControl** control, DifficultPreset &preset, RulesChecker **... checkers>
class GameHandler {
    DataManager *dataManager = nullptr;
    ThingsManager *thingsManager = nullptr;
    KeyControl *keyControl = nullptr;
    Field *field = nullptr;
    FieldScreen *mainScreen = nullptr;
    FightScreen *fightScreen = nullptr;
    bool isReady = false;
    bool finishEnable = false;


    bool checkFinishCondition() {
        return (... && (*checkers)->checkHero(field->getHero())) &&
               (... && (*checkers)->checkField(*field));
    }



    // для FieldScreen: start
    void generateField(int height, int width, int countWalls) {
        field = new Field(height, width, dataManager);
        if (field->generateFullField(countWalls)) {
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Поле было полностью сгенерировано"));
            field->setHeroOnStart();
            field->createHero();
            thingsManager = new ThingsManager(field);
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Информация о герое получена"));
        } else {
            std::cout << "Не удалось сгенерировать поле!\n";
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Не удалось сгенерировать поле"),
                                  LoggerPull::LoggingType::Error);
            throw -1;
        }
    }

    void requestMoveHero(CellPoint from, CellPoint to, std::string &gameAction) {
        if (!field->getGrid().isValidIndexes(to.getX(), to.getY()))
            return;
        bool moved = false;
        if (field->getHeroPos() == from) {
            moved = field->moveHero(to);
        }
        if (moved) {
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(to, "Герой сменил позицию"));
            auto thingOnPos = thingsManager->checkCellHasSmth(to);
            if (thingOnPos.first) {
                gameAction = mainScreen->createTitleForThingAction(thingOnPos.second->getNameThing(),
                                                                   thingOnPos.second->getProperties(),
                                                                   keyControl->getKeyByAction(
                                                                           mainScreen->getScreenName(),
                                                                           PlayerKeysControl::FIELD_TAKE_THING)
                                                                   );
            }
            if (field->getElem(to).getValue().getTypeCell() == TypeCell::FINISH) {
                finishEnable = checkFinishCondition();
                if (finishEnable) {
                    gameAction = "Вы на финишной клетке. Закончить игру? Нажмите ";
                    gameAction.push_back(
                            keyControl->getKeyByAction(mainScreen->getScreenName(), PlayerKeysControl::FIELD_FINISH_OUT));
                    gameAction += ", чтобы выйти.\n";
                }
            }
        }
    }

    bool requestMoveOut() {
        if (field->getElem(field->getHeroPos()).getValue().getTypeCell() == TypeCell::FINISH) {
            mainScreen->showHeroAchievement(field->getHero().getCountKilledEnemy());
            return true;
        }
        return false;
    }

    void requestTakeObject(CellPoint point) {
        auto thingOnPos = thingsManager->checkCellHasSmth(point);
        if (thingOnPos.first) {
            field->getHero().takeThing(thingOnPos.second);
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<Thing *>(thingOnPos.second, "Герой подобрал предмет"));
            if (thingOnPos.second->isVisualThing()) {
                field->getHero().resetModel(
                        dataManager->getHero(
                                field->getHero().hasThing(ThingObject::SWORD),
                                field->getHero().hasThing(ThingObject::ARMOR)));
            }
            thingsManager->deleteThingFromField(point);
        }
    }

    bool requestStartFight(CellPoint point) {
        int statusFight = 1;
        for (int i = -MainHero::getRangeVisibility(); i <= MainHero::getRangeVisibility(); ++i) {
            for (int j = -MainHero::getRangeVisibility(); j <= MainHero::getRangeVisibility(); ++j) {
                if (field->getEnemies().count(CellPoint(point.getX() + i, point.getY() + j))) {
                    mainScreen->clearScreen();
                    LoggerPull::writeData("gameLogs", LoggerDataAdapter<Character &>(
                            dynamic_cast<Character &>(this->field->getEnemyFromPoint(
                                    CellPoint(point.getX() + i, point.getY() + j))),
                            "Герой начал сражение с врагом"));


                    fightScreen = new FightScreen(this->field->getHero().getModel(), this->field->getEnemyFromPoint(
                            CellPoint(point.getX() + i, point.getY() + j)).getModel());
                    statusFight = fightStatusObserver(this->field->getHero(), this->field->getEnemyFromPoint(
                            CellPoint(point.getX() + i, point.getY() + j)));
                    delete fightScreen;
                    fightScreen = nullptr;


                    if (statusFight == FightStatus::KILLED_ENEMY) {
                        this->field->killEnemy(CellPoint(point.getX() + i, point.getY() + j));
                    } else if (statusFight == FightStatus::KILLED_HERO) {
                        LoggerPull::writeData("gameLogs", LoggerDataAdapter<Character &>(
                                dynamic_cast<Character &>(this->field->getEnemyFromPoint(
                                        CellPoint(point.getX() + i, point.getY() + j))),
                                "Герой побеждён врагом"));
                    }
                    return statusFight;
                }
            }
        }
        return statusFight;
    }

    bool registerMovement(int &action, std::string &gameAction) {
        action = keyControl->requestKeyAction(mainScreen->getScreenName());
        keyControl->requestTrashIgnore();
        CellPoint heroPos = field->getHeroPos();
        bool status = true;
        switch (action) {
            case PlayerKeysControl::FIELD_MOVE_UP:
                requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1), gameAction);
                return true;
            case PlayerKeysControl::FIELD_MOVE_DOWN:
                requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1), gameAction);
                return true;
            case PlayerKeysControl::FIELD_MOVE_LEFT:
                requestMoveHero(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()), gameAction);
                return true;
            case PlayerKeysControl::FIELD_MOVE_RIGHT:
                requestMoveHero(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()), gameAction);
                return true;
            case PlayerKeysControl::FIELD_FINISH_OUT:
                finishEnable = checkFinishCondition();
                if (finishEnable && requestMoveOut()) {
                    sleep(3);
                    action = PlayerKeysControl::FIELD_EXIT_FIELD;
                    LoggerPull::writeData("gameLogs",
                                          LoggerDataAdapter<std::string>("Игра окончена, игрок достиг финишной точки"));
                    return false;
                } else {
                    return true;
                }
            case PlayerKeysControl::FIELD_TAKE_THING:
                requestTakeObject(heroPos);
                finishEnable = checkFinishCondition();
                return true;
            case PlayerKeysControl::FIELD_START_FIGHT:
                status = requestStartFight(heroPos);
                if (status == FightStatus::KILLED_HERO) {
                    mainScreen->showMessage("Вы проиграли.\n");
                    mainScreen->showHeroAchievement(field->getHero().getCountKilledEnemy());
                    mainScreen->showMessage("Нажмите любую кнопку, чтобы выйти...\n");
                    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Игра окончена, игрок проиграл"));
                    keyControl->requestKeyIgnore();
                    action = PlayerKeysControl::FIELD_EXIT_FIELD;
                    return false;
                }
                finishEnable = checkFinishCondition();
                return true;
            case PlayerKeysControl::FIELD_EXIT_FIELD:
                LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Игра окончена, игрок вышел из игры"));
                return false;
            default:
                mainScreen->showMessage("Команда не распознана.\n");
        }
        return false;
    }

    void fieldStatusObserver() {
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начало процесса наблюдения за игрой"));
        int action = -1;
        keyControl->requestKeyIgnore(); // считываем перенос строки
        std::string message = "Для выхода введите ";
        message.push_back(keyControl->getKeyByAction(mainScreen->getScreenName(), PlayerKeysControl::FIELD_EXIT_FIELD));
        message += " и нажмите enter.\n";
        mainScreen->showMessage(message);
        mainScreen->showUpdatedScreen(field);
        mainScreen->showInventory(&(field->getHero()));
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>("Поле и инвентарь персонажа отображены в консоли"));
        while (action != PlayerKeysControl::FIELD_EXIT_FIELD) {
            std::string gameAction = "";
            field->incCountSteps();
            thingsManager->tryGenerateThing(field->getHero(), dataManager);
            bool goodMovement = registerMovement(action, gameAction);
            field->moveEnemies();
            if (goodMovement) {
                LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Смещение врагов"));
                mainScreen->clearScreen();
                field->createRandomEnemy();
                std::string message = "Для выхода введите ";
                message.push_back(
                        keyControl->getKeyByAction(mainScreen->getScreenName(), PlayerKeysControl::FIELD_EXIT_FIELD));
                message += " и нажмите enter.\n";
                mainScreen->showMessage(message);
                mainScreen->showUpdatedScreen(field);
                mainScreen->showMessage(gameAction + "\n");
                mainScreen->showEnemyInfo(&(field->getEnemies()));
                mainScreen->showInventory(&(this->field->getHero()));
            }
        }
        mainScreen->clearScreen();
    }
    // end

    // для FightScreen: start
    int fightStatusObserver(MainHero &mainHero, Enemy &enemy) {
        int selectedThing = 0;
        fightScreen->showUpdatedScreen(mainHero, selectedThing);
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Отображён экран боя"));
        fightScreen->showHealthInfo(mainHero, enemy);
        while (mainHero.checkPositiveHealth() && enemy.checkPositiveHealth()) {
            int action = keyControl->requestKeyAction(fightScreen->getScreenName());
            keyControl->requestTrashIgnore();
            fightScreen->clearScreen();
            if (!requestFightAction(action, mainHero, enemy, selectedThing)) {
                return FightStatus::LEAVE_FIGHT;
            }
            fightScreen->showUpdatedScreen(mainHero, selectedThing);
            fightScreen->showHealthInfo(mainHero, enemy);
        }
        if (mainHero.checkPositiveHealth()) {
            mainHero.writeKill(enemy.getName());
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<Character>(dynamic_cast<Character &>(enemy),
                                                                           "Герой победил данного врага"));
            fightScreen->showMessage("Вы победили!\nНажмите любую кнопку, чтобы продолжить.");
            keyControl->requestKeyIgnore();
        }
        return mainHero.checkPositiveHealth();
    }

    bool requestFightAction(int action, MainHero &mainHero, Enemy &enemy, int &selectedThing) {
        std::vector<double> heroAttackInfo;
        std::vector<double> enemyAttackInfo;
        switch (action) {
            case PlayerKeysControl::FIGHT_ATTACK_ENEMY:
                LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Герой произвёл атаку"));
                heroAttackInfo = mainHero.requestAttack(dynamic_cast<Character &>(enemy));
                fightScreen->showAttackInfo("Hero", heroAttackInfo[0], heroAttackInfo[1] > 0, heroAttackInfo[2] > 0);
                LoggerPull::writeData("gameLogs", LoggerDataAdapter<MainHero &>(mainHero, "Статус героя"));
                enemyAttackInfo = enemy.requestAttack(dynamic_cast<Character &>(mainHero));
                fightScreen->showAttackInfo(enemy.getName(), enemyAttackInfo[0], enemyAttackInfo[1] > 0,
                                            enemyAttackInfo[2] > 0);
                LoggerPull::writeData("gameLogs",
                                      LoggerDataAdapter<Character &>(dynamic_cast<Character &>(enemy), "Статус врага"));
                break;
            case PlayerKeysControl::FIGHT_SELECT_THING_UP:
                if (0 <= selectedThing - 1)
                    selectedThing--;
                break;
            case PlayerKeysControl::FIGHT_SELECT_THING_DOWN:
                if (selectedThing + 1 < mainHero.getInventory().size())
                    selectedThing++;
                break;
            case PlayerKeysControl::FIGHT_USE_THING:
                if (!mainHero.useThing(selectedThing)) {
                    fightScreen->showMessage("Предмета нет или он не может быть использован\n");
                } else {
                    if (selectedThing >= mainHero.getInventory().size())
                        selectedThing = std::max((int)mainHero.getInventory().size() - 1, 0);
                }
                break;
            case PlayerKeysControl::FIGHT_EXIT_FIGHT:
                return false;
        }
        return true;
    }
    // end

    // для KeySettingsScreen: старт

    void showKeySettingsScreen() {
        int selectedMenuItem = 0;
        std::unordered_map<std::string, std::unordered_map<int, char>> keysActionControl;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> actionBind;
        {
            actionBind = keyControl->getAllActionsNameId();
            auto keyActionsBound = keyControl->getAllBindKeysId();

            for (const auto &action: keyActionsBound) {
                for (const auto &key: action.second) {
                    keysActionControl[action.first][key.second] = key.first;
                }
            }
        }
        KeySettingsScreen keySettingsScreen(&keysActionControl, actionBind);
        keySettingsScreen.showUpdatedScreen(selectedMenuItem);
        int action = -1;
        char newKey;
        bool goodReplace = false;
        while (true) {
            action = keyControl->requestKeyAction(keySettingsScreen.getScreenName());
            switch (action) {
                case KEYSETTINGS_SELECT_MENU_UP:
                    if (0 <= selectedMenuItem - 1)
                        selectedMenuItem--;
                    break;
                case KEYSETTINGS_SELECT_MENU_DOWN:
                    if (selectedMenuItem + 1 < keySettingsScreen.getMenuSize())
                        selectedMenuItem++;
                    break;
                case KEYSETTINGS_CHANGE_BIND:
                    keyControl->requestKeyIgnore(); // считываем пробел
                    newKey = keyControl->requestKeyChar();
                    goodReplace = keyControl->resetBindChar(keySettingsScreen.findNameScreenByAction(selectedMenuItem),
                                                            selectedMenuItem, newKey);
                    if (goodReplace)
                        keysActionControl[keySettingsScreen.findNameScreenByAction(selectedMenuItem)][selectedMenuItem] = newKey;
                    break;
                case KEYSETTINGS_EXIT_SETTINGS:
                    keyControl->requestTrashIgnore();
                    if (keyControl->checkAllKeyBound()) {
                        return;
                    }
            }
            keyControl->requestTrashIgnore();
            keySettingsScreen.clearScreen();
            keySettingsScreen.showUpdatedScreen(selectedMenuItem);
        }
    }
    // end

public:
    GameHandler() {
        keyControl = *control;
        dataManager = new DataManager(preset.getThingsParams());
        dataManager->uploadModels();
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Модели загружены"));
        mainScreen = new FieldScreen();
    }

    virtual ~GameHandler() {
        delete mainScreen;
        delete dataManager;
        delete field;
        delete thingsManager;
    }

    // для StartScreen: start
    void showStartScreen() {
        StartScreen startScreen;
        startScreen.clearScreen(); // нужно, чтобы убрать первую строчку в терминале с запуском игры
        int selectedItem = 0;
        startScreen.showUpdatedScreen(selectedItem);
        while (true) {
            int action = keyControl->requestKeyAction(startScreen.getScreenName());
            keyControl->requestTrashIgnore();
            switch (action) {
                case START_SELECT_MENU_UP:
                    if (0 <= selectedItem - 1)
                        selectedItem--;
                    break;
                case START_SELECT_MENU_DOWN:
                    if (selectedItem + 1 < startScreen.getMenuSize())
                        selectedItem++;
                    break;
                case START_GO_TO_MENU:
                    switch (selectedItem) {
                        case MenuItemID::START_NEW_GAME:
                            startScreen.clearScreen();
                            generateField();
                            observeField();
                            delete field;
                            delete thingsManager; // так как статистика вещей зависит от героя, а герой - от поля
                            field = nullptr;
                            thingsManager = nullptr;
                            break;
                        case MenuItemID::LOAD_GAME:
                            break;
                        case MenuItemID::KEY_SETTINGS:
                            startScreen.clearScreen();
                            showKeySettingsScreen();
                            break;
                        case MenuItemID::EXIT:
                            startScreen.clearScreen();
                            return;
                    }
                    break;
            }
            startScreen.clearScreen();
            startScreen.showUpdatedScreen(selectedItem);
        }
    }
    // end


    void generateField() {
        srand(time(0));

        CharacterProperties properties = preset.getCharactersParams().at("MainHero");
        MainHero::setDefaultProperties(properties);
        properties = preset.getCharactersParams().at("Monster");
        Monster::setDefaultProperties(properties);
        properties = preset.getCharactersParams().at("Archer");
        Archer::setDefaultProperties(properties);
        properties = preset.getCharactersParams().at("Gargoyle");
        Gargoyle::setDefaultProperties(properties);
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Характеристики персонажей загружены"));

        auto[height, width, countWalls] = mainScreen->showStartFieldScreen(keyControl);
        generateField(height, width, countWalls);
        field->setRules(preset.getCntEnemyOnField(), preset.getTimeBetweenGenerateEnemy());
        thingsManager->setRules(preset.getCntHealThing(), preset.getTimeBetweenGenerateVisualThing(),
                                preset.getTimeBetweenGenerateHealThing());
        isReady = true;
    }

    void observeField() {
        if (isReady) {
            fieldStatusObserver();
            mainScreen->clearScreen();
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начался процесс наблюдения за игрой"));
        } else {
            LoggerPull::writeData("gameLogs",
                                  LoggerDataAdapter<std::string>("Попытка начать наблюдение при незавершённом поле"),
                                  LoggerPull::LoggingType::Error);
        }

    }
};