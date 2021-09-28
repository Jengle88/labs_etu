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
	THING,
	HERO,
	ENEMY
};

class CellObject {
	int typeCell;
	int typeObject;
public:
	explicit CellObject(int typeCell = TypeCell::EMPTY, int typeObject = TypeObject::NOTHING): typeCell(typeCell), typeObject(typeObject) {}
    char getCellAsChar() const;
    int getTypeCell() const;
	void setTypeCell(TypeCell typeCell);
	int getTypeObject() const;
	void setTypeObject(TypeObject typeObject);
};

