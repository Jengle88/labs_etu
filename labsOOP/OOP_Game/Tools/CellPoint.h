class CellPoint {
	int x;
	int y;
public:
	CellPoint() = default;
	CellPoint(int x, int y): x(x), y(y) {}
	bool isIndexedCurr() const;
	int getX() const;
	int getY() const;
};