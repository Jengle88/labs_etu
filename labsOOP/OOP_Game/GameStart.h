#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Tools/Logger.hpp"

class GameStart {
public:
    static void startGameMode(std::string modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            Logger *logger = Logger::getInstance();
            auto *dataManager = new DataManager();
            dataManager->uploadModels();
            auto thing = dataManager->getHealthThing();
            Logger::writeDataToConsole(dataManager->getThing(1, ThingObject::SWORD), Logger::LoggingType::Warning,
                                       std::cout, "Attention!");
            std::string archer = "Archer";
            Logger::writeDataToConsole(Archer(dataManager->getModelCharacter(archer)));
            std::string monster = "Monster";
            Logger::writeDataToConsole(Monster(dataManager->getModelCharacter(monster)));
            std::string gargoyle = "Gargoyle";
            Logger::writeDataToConsole(Gargoyle(dataManager->getModelCharacter(gargoyle)));
            Logger::writeDataToConsole(MainHero(dataManager->getHero(true, true)));
            Logger::writeMessageToConsole("Aboba", Logger::LoggingType::Error);
//            FieldScreen mainScreen;
//            mainScreen.showStartFieldScreen(dataManager);
//            mainScreen.gameStatusObserver();
            delete dataManager;
            delete logger;
        }
        else if (modeName == "features") {
            int h = 30;
            int w = 30;
            int countWalls = 250;
            DataManager dataManager;
//            auto enemy = dataManager.getModelGargoyleWait();
//            for (int i = 0; i < enemy.size(); ++i) {
//                std::cout << enemy[i] << '\n';
//            }
//            auto hero = dataManager.getModelHeroHead();
//            for (int i = 0; i < dataManager.getModelHeroBodyWait(true, true).size(); ++i) {
//                hero.push_back(dataManager.getModelHeroBodyWait(true, true)[i]);
//            }
//            for (int i = 0; i < dataManager.getModelHeroLegs().size(); ++i) {
//                hero.push_back(dataManager.getModelHeroLegs()[i]);
//            }
//            for (int i = 0; i < hero.size(); ++i) {
//                std::cout << hero[i] << '\n';
//            }
//            Field field = Field(h, w);
//            field.generateFullField(countWalls);
//            field.setHeroOnStart();
//            field.createHero(25, 7, 2, 1);
//            field.hero.takeThing(ThingObject("aba", {1,2,3,0,0}, ThingObjectsName::SWORD, true, false));
//            int z1 = 2;
//            auto character = MainHero(CHARACTER_MAX_HEALTH, 1, 1, 0, 0);
//            field.hero.requestAttack(character);
//            field.hero.requestAttack(character);
//            field.hero.requestAttack(character);
//            field.hero.ejectThing(0);
//            int z2 = 2;
//    field.cleanStartFinishWay();
        }
    }
};