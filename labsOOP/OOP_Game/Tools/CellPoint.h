#pragma once
class CellPoint {
	int x;
	int y;
public:
	CellPoint(): x(0), y(0) {}
	CellPoint(int x, int y): x(x), y(y) {}
	bool isIndexedCurr() const;
	int getX() const;
	int getY() const;

    bool operator==(CellPoint point) const;
};