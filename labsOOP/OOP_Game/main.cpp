#include <iostream>
#include "UI/Models/Field.h"

/*
 * TODO: 1) Класс итератора для прохода по полю
 * TODO: 2) Конструктор копирования для поля
 * TODO: 3) Конструктор перемещения для поля
 *
 */

int main() {
	int h = 250;
	int w = 100;
    int countWalls = 500;
    int fullTime = clock();
    Field field = Field(h,w);
//    field.generateStartFinishWay();
//    std::cout << "Generate Start Finish: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
//    start = clock();
//    field.generateWay();
//    std::cout << "Generate Way to Finish: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
//    start = clock();
//    field.generateWalls(countWalls);
//    std::cout << "Generate Walls: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
//    start = clock();
    field.generateFullField(countWalls);
//    field.printField();
    auto iter = field.getFieldIterator();
    for (int i = 0; i < field.getHeight(); ++i) {
        for (int j = 0; j < field.getWidth(); ++j) {
            std::cout << iter.getElem().getValue().getTypeCell();
            iter.moveRight();
        }
        std::cout << '\n';
        iter.moveDownAndStart();
    }
//    std::cout << "Full time: " << double(clock() - fullTime) / CLOCKS_PER_SEC << '\n';
    int z = 2;
    //	Grid grid = Grid(h,w);
//	for (int i = 0; i < h; ++i) {
//		for (int j = 0; j < w; ++j) {
//			grid.setElem(CellPoint(i,j), Cell(CellObject()));
//			std::cout << grid.getElem(CellPoint(i, j)).getValue().getTypeCell() << ' ';
//		}
//		std::cout << '\n';
//	}
//	std::cout << '\n';
//	h = 3;
//	w = 3;
//	grid.resizeGrid(h,w);
//	for (int i = 0; i < h; ++i) {
//		for (int j = 0; j < w; ++j) {
//			grid.setElem(CellPoint(i,j), Cell(CellObject()));
//			std::cout << grid.getElem(CellPoint(i, j)).getValue().getTypeCell() << ' ';
//		}
//		std::cout << '\n';
//	}
	return 0;
}
