#include <iostream>
#include "UI/Models/Field.h"

int main() {
	int h = 100;
	int w = 100;
    int start = clock();
    int fullTime = start;
    Field field = Field(h,w);
    field.generateStartFinish();
    std::cout << "Generate Start Finish: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    field.generateWayToFinish();
    std::cout << "Generate Way to Finish: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    field.generateWalls(250);
    std::cout << "Generate Walls: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    field.printField();
    std::cout << "Print Field: " << double(clock() - start) / CLOCKS_PER_SEC << '\n';
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
