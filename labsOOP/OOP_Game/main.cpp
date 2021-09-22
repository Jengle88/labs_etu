#include <iostream>
#include "UI/Models/Field.h"

int main() {
	int h = 30;
	int w = 30;
    int countWalls = 500;
    int fullTime = clock();
    Field field = Field(h,w);
    field.generateFullField(countWalls);
    std::cout << "Full generate time: " << double(clock() - fullTime) / CLOCKS_PER_SEC << '\n';
    field.printField();
    auto iter = field.getFieldIterator();
    for (int i = 0; i < field.getHeight(); ++i) {
        for (int j = 0; j < field.getWidth(); ++j) {
            std::cout << iter.getElem().getValue().getTypeCellAsChar();
            iter++;
        }
        std::cout << '\n';
    }
    int copyTime = clock();
    Field copyField = field;
    std::cout << "Full copy time: " << double(clock() - copyTime) / CLOCKS_PER_SEC << '\n';
    FieldIterator copyIter = copyField.getFieldIterator();
    for (int i = 0; i < 5; ++i) {
        copyIter.setElem(Cell(CellObject(TypeCell::START, TypeObject::NOTHING)));
        copyIter++;
    }
    copyField.printField();

    int moveTime = clock();
    Field moveField = std::move(field);
    std::cout << "Full move time: " << double(clock() - moveTime) / CLOCKS_PER_SEC << '\n';
    FieldIterator moveIter = moveField.getFieldIterator();
    for (int i = 0; i < 5; ++i) {
        moveIter.setElem(Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING)));
        moveIter++;
    }
    moveField.printField();
	return 0;
}
