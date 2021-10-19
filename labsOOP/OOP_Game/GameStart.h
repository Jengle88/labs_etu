#include <string>
#include "UI/FieldScreen.h"

class GameStart {
public:
    static void startGameMode(std::string modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            FieldScreen mainScreen;
            mainScreen.showStartFieldScreen();
            mainScreen.gameStatusObserver();
        }
        else if (modeName == "demo")
        {
            int h = 30;
            int w = 30;
            int countWalls = 500;
            int fullTime = clock();

            Field field1 = Field(h, w);
            field1.generateFullField(countWalls);
            std::cout << "Full generate time: " << double(clock() - fullTime) / CLOCKS_PER_SEC << '\n';
            std::cout << "Print with func:\n";
            field1.printField();
            auto iter = field1.getFieldIterator();
            std::cout << "Print with iterator:\n";
            for (int i = 0; i < field1.getHeight(); ++i) {
                for (int j = 0; j < field1.getWidth(); ++j) {
                    std::cout << iter.getElem().getValue().getCellAsChar();
                    iter++;
                }
                std::cout << '\n';
            }

            std::cout << "Generate second Field\n";
            Field field2 = Field(h+1, w+1);
            field2.generateFullField(countWalls);

            int copyTime = clock();
            Field copyField = field1;
            std::cout << "Full copy constr time: " << double(clock() - copyTime) / CLOCKS_PER_SEC << '\n';
            copyTime = clock();
            copyField = field2;
            std::cout << "Full copy operator= time: " << double(clock() - copyTime) / CLOCKS_PER_SEC << '\n';
//    FieldIterator copyIter = copyField.getFieldIterator();
//    for (int i = 0; i < 5; ++i) {
//        copyIter.setElem(Cell(CellObject(TypeCell::START, TypeObject::NOTHING)));
//        copyIter++;
//    }
            std::cout << "Print copied field1:\n";
            copyField.printField();

            int moveTime = clock();
            Field moveField = std::move(field1);
            std::cout << "Full move constr time: " << double(clock() - moveTime) / CLOCKS_PER_SEC << '\n';
            moveTime = clock();
            moveField = std::move(field2);
            std::cout << "Full move operator= time: " << double(clock() - moveTime) / CLOCKS_PER_SEC << '\n';
            moveField.printField();
//    FieldIterator moveIter = moveField.getFieldIterator();
//    moveIter.moveTo(5, 0);
//    for (int i = 0; i < 5; ++i) {
//        moveIter.setElem(Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING)));
//        moveIter++;
//    }
//    std::cout << "Print moved field1:\n";
//    moveField.printField();
            std::cout << "Cleaned way-symbols\n";
        }
        else if (modeName == "features")
        {
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
//            field.hero.takeThing(Thing("aba", {1,2,3,0,0}, ThingObject::SWORD, true, false));
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