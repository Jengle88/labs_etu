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

template<RulesPreset & preset, GlobalRules<preset> & rules>
class GameHandler {
    DataManager* dataManager = nullptr;
    ThingsManager* thingsManager = nullptr;
    Field* field = nullptr;
    FieldScreen* mainScreen = nullptr;
    bool isReady = false;
    bool finishEnable = false;


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

    char getKey() const {
        char action = getchar();
        std::cin.ignore(32767, '\n');
        return action;
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
                gameAction = mainScreen->generateTitleForThingAction(thingOnPos.second.getNameThing(),
                                                                     thingOnPos.second.getProperties(), HeroKeyControl::TAKE);
            }
            if (field->getElem(to).getValue().getTypeCell() == TypeCell::FINISH)
                gameAction = "Вы на финишной клетке. Закончить игру? Нажмите q, чтобы выйти.\n";
        }
    }

    bool requestMoveOut() {
        if (field->getElem(field->getHeroPos()).getValue().getTypeCell() == TypeCell::FINISH) {
            Printer::printHeroAchievement(field->getHero().getCountKilledEnemy());
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
        for (int i = -MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; i <= MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; ++i) {
            for (int j = -MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; j <= MainHero::MainHeroProperties::MAIN_HERO_RANGE_VISIBILITY; ++j) {
                if (field->getEnemies().count(CellPoint(point.getX() + i, point.getY() + j))) {
                    system("clear");
                    LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character&>(
                            dynamic_cast<Character&>(this->field->getEnemyFromPoint(CellPoint(point.getX() + i, point.getY() + j))),
                            "Герой начал сражение с врагом"));
                    auto fightScreen = FightScreen(this->field->getHero(), this->field->getEnemyFromPoint(
                            CellPoint(point.getX() + i, point.getY() + j)), this->dataManager);
                    statusFight = fightScreen.fightObserver();
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
                if (requestMoveOut()) {
                    sleep(3);
                    action = HeroKeyControl::EXIT;
                    LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Игра окончена, игрок достиг финишной точки"));
                    return false;
                } else {
                    return true;
                }
            case HeroKeyControl::TAKE:
                requestTakeObject(heroPos);
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
                return true;
            case HeroKeyControl::EXIT:
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Игра окончена, игрок вышел из игры"));
                return false;
            default:
                mainScreen->showMessage("Команда не распознана.\n");
        }
        return false;
    }

    void gameStatusObserver() {
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Начало процесса наблюдения за игрой"));
        char action = getchar(); // считываем перенос строки
        mainScreen->showMessage("Для выхода введите ` и нажмите enter.\n");
        mainScreen->showUpdatedScreen(field);
        mainScreen->showInventory(&(field->getHero()));
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Поле и инвентарь персонажа отображены в консоли"));
        while (action != HeroKeyControl::EXIT) {
            std::string gameAction = "";
            bool goodMovement = registerMovement(action, gameAction);
            field->moveEnemies();
            if (goodMovement) {
                LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Смещение врагов"));
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

public:
    GameHandler() {
        dataManager = new DataManager(rules.getThingRules());
    }

    void start() {
        srand(time(0));
        dataManager->uploadModels();
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Модели загружены"));
        mainScreen = new FieldScreen();
        auto [height, width, countWalls] = mainScreen->showStartFieldScreen(dataManager);
        generateField(height, width, countWalls);
        isReady = true;
    }

    virtual ~GameHandler() {
        delete mainScreen;
        delete dataManager;
        delete field;
        delete thingsManager;
    }

    void observe() {
        if (isReady) {
            gameStatusObserver();
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начался процесс наблюдения за игрой"));
        } else {
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Попытка начать наблюдение при незавершённом поле"), LoggerPull::LoggingType::Error);
        }

    }
};