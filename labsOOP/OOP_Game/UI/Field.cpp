#include <cstdlib>
#include "Field.h"

Field::Field() {
	wayGenerated = false;
	chosenStartFinish = false;
}

Field::Field(const Grid &field, CellPoint start, CellPoint finish) {
	this->field = field;
	if (isCorrectStartFinish(start, finish)) {
		this->start = start;
		this->finish = finish;
		chosenStartFinish = true;
	}
}

bool Field::isValidIndexes(int x, int y) const {
	return 0 <= x && x < field.getWidth() && 0 <= y && y < field.getHeight();
}

bool Field::isCorrectStartFinish(CellPoint start, CellPoint finish) const {
	return isValidIndexes(start.getX(), start.getY()) &&
	       isValidIndexes(finish.getX(), finish.getY()) &&
	       abs(start.getX() - finish.getX()) + abs(start.getY() - finish.getY()) >= 2;
}

void Field::generateStartFinish() {


}
