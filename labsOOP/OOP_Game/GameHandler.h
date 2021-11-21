#pragma once
#include "Rules/GlobalRules.h"
#include "Rules/RulesPreset.h"
#include "Data/DataManager.h"
#include "UI/FieldScreen.h"
#include "Logger/LoggerDataAdapter.h"
#include "Logger/LoggerPull.h"


enum HeroKeyControl{
    UP = 'w',
    LEFT = 'a',
    RIGHT = 'd',
    DOWN = 's',
    TAKE = 'e',
    FIGHT = 'f',
    FINISH_OUT = 'q',
    EXIT = '`'
};

enum FightStatus {
    LEAVE_FIGHT = -1,
    KILLED_ENEMY = 1,
    KILLED_HERO = 0
};

enum FightHeroKeyAction {
    ATTACK = 'a',
    USE = 'e'
};

template<RulesPreset & preset, GlobalRules<preset> & rules>
class GameHandler {
    DataManager* dataManager = nullptr;
    ThingsManager* thingsManager = nullptr;
    Field* field = nullptr;
    FieldScreen* mainScreen = nullptr;
    FightScreen* fightScreen = nullptr;
    bool isReady = false;
    bool finishEnable = false;


    char getKey() const {
        char action = getchar();
        std::cin.ignore(32767, '\n');
        return action;
    }

    // для FieldScreen: start
    void generateField(int height, int width, int countWalls) {
        field = new Field(height, width, dataManager);
        if (field->generateFullField(countWalls)) {
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Поле было полностью сгенерировано"));
            field->setHeroOnStart();
            field->createHero();
            thingsManager = new ThingsManager(field);
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Информация о герое получена"));
        } else {
            std::cout << "Не удалось сгенерировать поле!\n";
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Не удалось сгенерировать поле"), LoggerPull::LoggingType::Error);
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
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<CellPoint>(to, "Герой сменил позицию"));
            auto thingOnPos = thingsManager->checkCellHasSmth(to);
            if (thingOnPos.first) {
                gameAction = mainScreen->createTitleForThingAction(thingOnPos.second.getNameThing(),
                                                                   thingOnPos.second.getProperties(),
                                                                   HeroKeyControl::TAKE);
            }
            if (field->getElem(to).getValue().getTypeCell() == TypeCell::FINISH && finishEnable)
                gameAction = "Вы на финишной клетке. Закончить игру? Нажмите q, чтобы выйти.\n";
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
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<Thing>(thingOnPos.second, "Герой подобрал предмет"));
            if (thingOnPos.second.isVisualThing()) {
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
                    system("clear");
                    LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character&>(
                            dynamic_cast<Character&>(this->field->getEnemyFromPoint(CellPoint(point.getX() + i, point.getY() + j))),
                            "Герой начал сражение с врагом"));



                    fightScreen = new FightScreen(this->field->getHero().getModel(), this->field->getEnemyFromPoint(
                            CellPoint(point.getX() + i, point.getY() + j)).getModel()/*, this->dataManager*/);
                    statusFight = fightStatusObserver(this->field->getHero(), this->field->getEnemyFromPoint(
                            CellPoint(point.getX() + i, point.getY() + j))); // fightScreen->fightObserver();
                    delete fightScreen;
                    fightScreen = nullptr;



                    if (statusFight == FightStatus::KILLED_ENEMY) {
                        this->field->killEnemy(CellPoint(point.getX() + i, point.getY() + j));
                    } else if (statusFight == FightStatus::KILLED_HERO) {
                        LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character&>(
                                dynamic_cast<Character&>(this->field->getEnemyFromPoint(CellPoint(point.getX() + i, point.getY() + j))),
                                "Герой побеждён врагом"));
                    }
                    return statusFight;
                }
            }
        }
        return statusFight;
    }

    bool registerMovement(char &action, std::string &gameAction) {
        action = getKey();
        CellPoint heroPos = field->getHeroPos();
        thingsManager->tryGenerateThing(field->getHero(), dataManager);
        std::pair<bool, Thing> thingOnPos;
        bool status = true;
        switch (tolower(action)) {
            case HeroKeyControl::UP:
                requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() - 1), gameAction);
                return true;
            case HeroKeyControl::DOWN:
                requestMoveHero(heroPos, CellPoint(heroPos.getX(), heroPos.getY() + 1), gameAction);
                return true;
            case HeroKeyControl::LEFT:
                requestMoveHero(heroPos, CellPoint(heroPos.getX() - 1, heroPos.getY()), gameAction);
                return true;
            case HeroKeyControl::RIGHT:
                requestMoveHero(heroPos, CellPoint(heroPos.getX() + 1, heroPos.getY()), gameAction);
                return true;
            case HeroKeyControl::FINISH_OUT:
                if (finishEnable && requestMoveOut()) {
                    sleep(3);
                    action = HeroKeyControl::EXIT;
                    LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Игра окончена, игрок достиг финишной точки"));
                    return false;
                } else {
                    return true;
                }
            case HeroKeyControl::TAKE:
                requestTakeObject(heroPos);
                finishEnable = rules.checkFinishCondition(field->getHero());
                return true;
            case HeroKeyControl::FIGHT:
                status = requestStartFight(heroPos);
                if (status == FightStatus::KILLED_HERO) {
                    mainScreen->showMessage("Вы проиграли.\n");
                    mainScreen->showHeroAchievement(field->getHero().getCountKilledEnemy());
                    mainScreen->showMessage("Нажмите любую кнопку, чтобы выйти...\n");
                    LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Игра окончена, игрок проиграл"));
                    getchar();
                    action = HeroKeyControl::EXIT;
                    return false;
                }
                finishEnable = rules.checkFinishCondition(field->getHero());
                return true;
            case HeroKeyControl::EXIT:
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Игра окончена, игрок вышел из игры"));
                return false;
            default:
                mainScreen->showMessage("Команда не распознана.\n");
        }
        return false;
    }

    void fieldStatusObserver() {
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начало процесса наблюдения за игрой"));
        char action = getchar(); // считываем перенос строки
        mainScreen->showMessage("Для выхода введите ` и нажмите enter.\n");
        mainScreen->showUpdatedScreen(field);
        mainScreen->showInventory(&(field->getHero()));
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>("Поле и инвентарь персонажа отображены в консоли"));
        while (action != HeroKeyControl::EXIT) {
            std::string gameAction = "";
            field->incCountSteps();
            bool goodMovement = registerMovement(action, gameAction);
            field->moveEnemies();
            if (goodMovement) {
                LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Смещение врагов"));
                std::system("clear");
                field->createRandomEnemy();
                mainScreen->showMessage("Для выхода введите ` и нажмите enter.\n");
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
    int fightStatusObserver(MainHero& mainHero, Enemy & enemy) {
        fightScreen->showUpdatedScreen(mainHero);
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Отображён экран боя"));
        fightScreen->showHealthInfo(mainHero, enemy);
        while (mainHero.checkPositiveHealth() && enemy.checkPositiveHealth()) {
            char action = getchar();
            fightScreen->clearScreen();
            if (!requestFightAction(action, mainHero, enemy)) {
                getchar(); // считываем перенос строки
                return FightStatus::LEAVE_FIGHT;
            }
            fightScreen->showUpdatedScreen(mainHero);
            fightScreen->showHealthInfo(mainHero, enemy);
        }
        if (mainHero.checkPositiveHealth()) {
            mainHero.writeKill(enemy.getName());
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character>(dynamic_cast<Character&>(enemy), "Герой победил данного врага"));
            fightScreen->showMessage("Вы победили!\nНажмите любую кнопку, чтобы продолжить.");
            getchar();
        }
        return mainHero.checkPositiveHealth();
    }

    bool requestFightAction(char action, MainHero& mainHero, Enemy& enemy) {
        int numberThing = -1;
        std::vector<double> heroAttackInfo;
        std::vector<double> enemyAttackInfo;
        switch (tolower(action)) {
            case FightHeroKeyAction::ATTACK:
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Герой произвёл атаку"));
                heroAttackInfo = mainHero.requestAttack(dynamic_cast<Character&>(enemy));
                fightScreen->showAttackInfo("Hero", heroAttackInfo[0], heroAttackInfo[1] > 0, heroAttackInfo[2] > 0);
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<MainHero&>(mainHero, "Статус героя"));
                enemyAttackInfo = enemy.requestAttack(dynamic_cast<Character &>(mainHero));
                fightScreen->showAttackInfo(enemy.getName(), enemyAttackInfo[0], enemyAttackInfo[1] > 0, enemyAttackInfo[2] > 0);
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character&>(dynamic_cast<Character&>(enemy), "Статус врага"));
                break;
            case FightHeroKeyAction::USE:
                std::cin >> numberThing;
                if (!mainHero.useThing(numberThing - 1)) {
                    fightScreen->showMessage("Предмета нет или он не может быть использован\n");
//                std::cout << "Предмета нет или он не может быть использован\n";
                }
                break;
            case HeroKeyControl::EXIT:
                return false;
        }
        std::cin.ignore(32767, '\n');
        return true;
    }
    // end

public:
    GameHandler() {
        dataManager = new DataManager(preset.getThingParams());
    }

    virtual ~GameHandler() {
        delete mainScreen;
        delete dataManager;
        delete field;
        delete thingsManager;
    }

    void generate() {
        srand(time(0));
        dataManager->uploadModels();
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Модели загружены"));

        CharacterProperties properties = preset.getCharactersParams().at("MainHero");
        MainHero::setDefaultProperties(properties.name, properties.health, properties.attackPower, properties.protection,
                                       properties.luck, properties.visibility, properties.criticalFactor, properties.dodgeFactor);
        properties = preset.getCharactersParams().at("Monster");
        Monster::setDefaultProperties(properties.name, properties.health, properties.attackPower, properties.protection,
                                      properties.luck, properties.visibility, properties.criticalFactor, properties.dodgeFactor,
                                      properties.percentForFollowToHero, properties.lengthMove, properties.chanceToBeGenerate);
        properties = preset.getCharactersParams().at("Archer");
        Archer::setDefaultProperties(properties.name, properties.health, properties.attackPower, properties.protection,
                                     properties.luck, properties.visibility, properties.criticalFactor, properties.dodgeFactor,
                                     properties.percentForFollowToHero, properties.lengthMove, properties.chanceToBeGenerate);
        properties = preset.getCharactersParams().at("Gargoyle");
        Gargoyle::setDefaultProperties(properties.name, properties.health, properties.attackPower, properties.protection,
                                       properties.luck, properties.visibility, properties.criticalFactor, properties.dodgeFactor,
                                       properties.percentForFollowToHero, properties.lengthMove, properties.chanceToBeGenerate);
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Характеристики персонажей загружены"));

        mainScreen = new FieldScreen();
        auto [height, width, countWalls] = mainScreen->showStartFieldScreen(dataManager);
        generateField(height, width, countWalls);
        field->setRules(preset.getCntEnemyOnField(), preset.getTimeBetweenGenerateEnemy());
        thingsManager->setRules(preset.getCntHealThing(), preset.getTimeBetweenGenerateVisualThing(), preset.getTimeBetweenGenerateHealThing());
        isReady = true;
    }

    void observe() {
        if (isReady) {
            fieldStatusObserver();
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начался процесс наблюдения за игрой"));
        } else {
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Попытка начать наблюдение при незавершённом поле"), LoggerPull::LoggingType::Error);
        }

    }
};