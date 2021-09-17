#include "Cell.h"

CellObject Cell::getValue() const {
	return this->value;
}

void Cell::setValue(CellObject value) {
	this->value = value;
}

