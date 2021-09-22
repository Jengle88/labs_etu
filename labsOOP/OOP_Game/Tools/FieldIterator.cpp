#include "FieldIterator.h"

void FieldIterator::moveUp() {
    if (rootGrid->isValidYPos(posY - 1))
        posY--;
}

void FieldIterator::moveDown() {
    if (rootGrid->isValidYPos(posY + 1))
        posY++;
}

void FieldIterator::moveRight() {
    if (rootGrid->isValidXPos(posX + 1))
        posX++;
}

void FieldIterator::moveLeft() {
    if (rootGrid->isValidXPos(posX - 1))
        posX--;
}

void FieldIterator::moveTo(int deltaX, int deltaY) {
    if (rootGrid->isValidIndexes(posX + deltaX, posY + deltaY)) {
        posX += deltaX;
        posY += deltaY;
    }

}

Cell FieldIterator::getElem() const {
    return rootGrid->getElem(CellPoint(posX, posY));
}

void FieldIterator::moveDownAndStart() {
    if (rootGrid->isValidIndexes(0, posY + 1)) {
        posX = 0;
        posY++;
    }
}
