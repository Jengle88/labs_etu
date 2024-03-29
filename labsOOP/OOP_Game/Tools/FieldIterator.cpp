#include "FieldIterator.h"
#include "../Logger/LoggerPull.h"

Cell FieldIterator::getElem() const {
    if (rootGrid->isValidIndexes(posX, posY))
        return rootGrid->getElem(CellPoint(posX, posY));
    else {
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>("Были переданы невалидные индексы в getElem"),
                              LoggerPull::LoggingType::Error);
        throw std::invalid_argument("Были переданы невалидные индексы в getElem");
    }
}

CellPoint FieldIterator::getCurrentPosition() const {
    return {posX, posY};
}

void FieldIterator::moveDelta(int deltaX, int deltaY) {
    if (rootGrid->isValidIndexes(posX + deltaX, posY + deltaY)) {
        posX += deltaX;
        posY += deltaY;
    }
}

void FieldIterator::moveTo(int posX, int posY) {
    if (rootGrid->isValidIndexes(posX, posY)) {
        this->posX = posX;
        this->posY = posY;
    }
}

FieldIterator& FieldIterator::operator++() {
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
        return *this;
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
