#include "CellObject.h"

int CellObject::getTypeCell() const {
	return this->typeCell;
}

int CellObject::getTypeObject() const {
	return this->typeObject;
}

void CellObject::setTypeCell(TypeCell typeCell) {
	this->typeCell = typeCell;
}

void CellObject::setTypeObject(TypeObject typeObject) {
	this->typeObject = typeObject;
}

char CellObject::getTypeCellAsChar() const {
    switch (this->getTypeCell()) {
        case TypeCell::WAY:
            return '#';
        case TypeCell::WALL:
            return '.';
        case TypeCell::START:
            return 'S';
        case TypeCell::FINISH:
            return 'F';
        case TypeCell::EMPTY:
            return ' ';
    }
    return '?';
}

