#include <utility>
#include "../../Objects/CellObject.h"
#include "../../Tools/CellPoint.h"

class Cell {
	CellObject value;
public:
	Cell() = default;
	Cell(CellObject value): value(value){}

	CellObject getValue() const;
	void setValue(CellObject val);

};

