#include "Vector2D.h"

Vector2D Vector2D::operator+(const Vector2D &other) const {
    return { this->x + other.x, this->y + other.y };
}

Vector2D Vector2D::operator-(const Vector2D &other) const {
    return { this->x - other.x, this->y - other.y };
}

Vector2D Vector2D::operator*(const Vector2D &other) const {
    return { this->x * other.x, this->y * other.y };
}

Vector2D Vector2D::operator/(const Vector2D &other) const {
    return { this->x / other.x, this->y / other.y };
}
