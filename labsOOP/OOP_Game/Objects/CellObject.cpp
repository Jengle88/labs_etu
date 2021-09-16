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

