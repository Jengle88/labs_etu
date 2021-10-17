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

bool operator==(const CellPoint &point1, const CellPoint &point2) {
    return point1.x == point2.x && point1.y == point2.y;
}

bool operator<(const CellPoint &point1, const CellPoint& point2) {
    return point1.y < point2.y || point1.y == point2.y && point1.x < point2.x;
}

