#include <utility>
#include "../../Objects/CellObject.h"
#include "../../Tools/CellPoint.h"

class Cell {
	int val;
public:
	Cell() = default;
	Cell(int val): val(val){}

	int getVal() const;
	void setVal(int val);

};

