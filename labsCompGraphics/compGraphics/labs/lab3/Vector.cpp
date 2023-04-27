#include "Vector.h"

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector Vector::operator+(Vector vector2) const {
    return {x + vector2.x, y + vector2.y};
}

Vector Vector::operator-(Vector vector2) const {
    return {x - vector2.x, y - vector2.y};
}

double Vector::angle() const {
    return std::atan2(y, x);
}

double Vector::len() const {
    return hypot(x, y);
}

Vector Vector::rotate(double a) const {
    return {cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y};
}
