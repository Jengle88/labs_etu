enum TypeCell {
	EMPTY,
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
	CellObject(): typeCell(TypeCell::EMPTY), typeObject(TypeObject::NOTHING){}
	explicit CellObject(int typeCell = TypeCell::EMPTY, int typeObject = TypeObject::NOTHING): typeCell(typeCell), typeObject(typeObject) {}
	int getTypeCell() const;
	void setTypeCell(TypeCell typeCell);
	int getTypeObject() const;
	void setTypeObject(TypeObject typeObject);
};
