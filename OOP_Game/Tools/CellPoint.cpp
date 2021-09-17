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