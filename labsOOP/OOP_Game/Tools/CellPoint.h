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

    friend bool operator==(const CellPoint& point1, const CellPoint& point2);
    friend bool operator<(const CellPoint& point1, const CellPoint& point2);
};