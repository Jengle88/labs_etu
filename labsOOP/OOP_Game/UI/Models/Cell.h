#pragma once
#include "../../Objects/CellObject.h"
#include "../../Tools/CellPoint.h"

class Cell {
	CellObject value;
public:
	Cell() = default;
	explicit Cell(CellObject value);

	CellObject getValue() const;
	void setValue(CellObject val);

};

