#include "../UI/Models/Cell.h"
#include <exception>

#define UP_LIMIT_HEIGHT (int)1e4
#define DOWN_LIMIT_HEIGHT (int)2
#define UP_LIMIT_WIDTH (int)1e4
#define DOWN_LIMIT_WIDTH (int)2

class Grid {
	int height;
	int width;
	Cell** grid;

	bool isValidIndexes(int x, int y) const;
	bool isValidHeight(int height) const;
	bool isValidWidth(int width) const;
	bool isValidSizes(int height, int width) const;
    void init(int height, int width);
public:
	Grid();
	Grid(int height, int width);
	Grid(int height, int width, Cell **grid);
    ~Grid();

	int getHeight() const;
	int getWidth() const;
	void setElem(CellPoint point, Cell cell);
	Cell getElem(CellPoint point) const;
	void clear();
	void resizeGrid(int height, int width, Cell **newGrid = nullptr);
    friend class Field;
};
