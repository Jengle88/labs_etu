#pragma once
enum TypeCell {
	EMPTY,
	WAY,
	WALL,
	START,
	FINISH
};

enum TypeObject {
	NOTHING,
	HERO,
	ENEMY
};

class CellObject {
	int typeCell;
	int typeObject;
    bool hasThing;
public:
	explicit CellObject(int typeCell = TypeCell::EMPTY, int typeObject = TypeObject::NOTHING, bool hasThing = false): typeCell(typeCell), typeObject(typeObject), hasThing(hasThing) {}
    char getCellAsChar() const;
    int getTypeCell() const;
    int getTypeObject() const;
    bool isThing() const;
};

