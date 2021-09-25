#include "CellPoint.h"

bool CellPoint::isIndexedCurr() const {
	return 0 <= this->x && 0 <= this->y;
}

int CellPoint::getX() const {
	return this->x;
}

int CellPoint::getY() const {
	return this->y;
}

bool CellPoint::operator==(CellPoint point) const {
    return this->x == point.x && this->y == point.y;
}
