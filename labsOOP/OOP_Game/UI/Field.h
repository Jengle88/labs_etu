#include "../Tools/Grid.h"

class Field {
	Grid field;
	CellPoint start;
	CellPoint finish;
	bool wayGenerated;
	bool chosenStartFinish;
	bool isCorrectStartFinish(CellPoint start, CellPoint finish) const;
	bool isValidIndexes(int x, int y) const;
public:
	Field();
	Field(const Grid& field, CellPoint start, CellPoint finish);
	void generateStartFinish();
	void generateWayToFinish();

};

