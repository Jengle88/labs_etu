#include "CellObject.h"

char CellObject::getCellAsChar() const {
    char typeCell = '?';
    switch (this->getTypeCell()) {
        case TypeCell::WAY:
            typeCell = '#';
            break;
        case TypeCell::WALL:
            typeCell = '+';
            break;
        case TypeCell::START:
            typeCell = 'S';
            break;
        case TypeCell::FINISH:
            typeCell = 'F';
            break;
        case TypeCell::EMPTY:
            typeCell = ' ';
            break;
    }
    char typeObject = '?';
    switch (this->getTypeObject()) {
        case TypeObject::HERO:
            typeObject = 'H';
            break;
        case TypeObject::ENEMY:
            typeObject = 'E';
            break;
    }
    char thingObject = this->hasThing ? 'T' : '?';
    if (typeObject != '?')
        return typeObject;
    else if (thingObject != '?')
        return thingObject;
    else
        return typeCell;
}

int CellObject::getTypeCell() const {
	return this->typeCell;
}

void CellObject::setTypeCell(TypeCell typeCell) {
    this->typeCell = typeCell;
}

int CellObject::getTypeObject() const {
	return this->typeObject;
}

void CellObject::setTypeObject(TypeObject typeObject) {
	this->typeObject = typeObject;
}

bool CellObject::isThing() const {
    return hasThing;
}

