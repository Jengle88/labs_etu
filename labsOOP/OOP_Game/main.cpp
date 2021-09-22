#include <iostream>
#include "UI/Models/Field.h"

int main() {
	int h = 250;
	int w = 100;
    int countWalls = 300;
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
    field.printField();
    std::cout << "Full time: " << double(clock() - fullTime) / CLOCKS_PER_SEC << '\n';
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
