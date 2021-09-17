#include "../UI/Models/Cell.h"
#include <exception>

#define UP_LIMIT_HEIGHT (size_t)1e6
#define DOWN_LIMIT_HEIGHT (size_t)0
#define UP_LIMIT_WIDTH (size_t)1e6
#define DOWN_LIMIT_WIDTH (size_t)0

class Grid {
	int height;
	int width;
	Cell** grid;

	bool isValidIndexes(int height, int width) const;
	bool isValidSizes(int height, int width) const;
public:
	Grid(int height, int width);
	Grid(int height, int width, Cell **grid);
	~Grid();

	void setElem(CellPoint point, Cell cell);
	Cell getElem(CellPoint point) const;
	void clear();
	void resizeGrid(int height, int width, Cell **newGrid = nullptr);
};
