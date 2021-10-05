#include <iostream>
#include "UI/Models/Field.h"
#include "UI/FieldScreen.h"


//#define GAME // Запускать через терминал
#define DEMO
//#define FEATURES



int main() {
#ifdef GAME
    std::setlocale(LC_ALL, "");
    FieldScreen mainScreen;
    mainScreen.showStartFieldScreen();
    mainScreen.gameStatusObserver();
#endif

#ifdef DEMO
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
#endif

#ifdef FEATURES
    int h = 30;
    int w = 30;
    int countWalls = 400;
    Field field = Field(h, w);
    field.generateFullField(countWalls);
    Field field1 = field;
    field1.printField();
//    field.cleanStartFinishWay();
#endif
    return 0;
}
