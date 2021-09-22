#include "FieldIterator.h"

void FieldIterator::moveDelta(int deltaX, int deltaY) {
    if (rootGrid->isValidIndexes(posX + deltaX, posY + deltaY)) {
        posX += deltaX;
        posY += deltaY;
    }

}

FieldIterator &FieldIterator::operator++() {
    if (rootGrid->isValidIndexes(posX + 1, posY)) {
        posX++;
        return *this;
    }
    if (rootGrid->isValidIndexes(0, posY + 1)) {
        posX = 0;
        posY++;
        return *this;
    }
    posX = 0; // end-значение
    posY = rootGrid->getHeight();
    return *this;
}

FieldIterator FieldIterator::operator++(int) {
    FieldIterator prev = *this;
    ++(*this);
    return prev;
}

FieldIterator &FieldIterator::operator--() {
    if (rootGrid->isValidIndexes(posX - 1, posY)) {
        posX--;
        return *this;
    }
    if (rootGrid->isValidIndexes(rootGrid->getWidth() - 1, posY - 1)) {
        posX = rootGrid->getWidth() - 1;
        posY--;
    }
    posX = 0; // end-значение
    posY = rootGrid->getHeight();
    return *this;

}

FieldIterator FieldIterator::operator--(int) {
    auto prev = *this;
    --(*this);
    return prev;
}

void FieldIterator::moveTo(int posX, int posY) {
    if (rootGrid->isValidIndexes(posX, posY)) {
        this->posX = posX;
        this->posY = posY;
    }

}

Cell FieldIterator::getElem() const {
    if (rootGrid->isValidIndexes(posX, posY))
        return rootGrid->getElem(CellPoint(posX, posY));
    else
        throw std::exception();
}

CellPoint FieldIterator::getCurrentPosition() const {
    return {posX, posY};
}

void FieldIterator::setElem(Cell cell) {
    this->rootGrid->setElem(CellPoint(posX,posY), cell);
}