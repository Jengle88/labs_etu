#include "Cell.h"

Cell::Cell(CellObject value) : value(value) {}

CellObject Cell::getValue() const {
	return this->value;
}

void Cell::setValue(CellObject value) {
	this->value = value;
}
