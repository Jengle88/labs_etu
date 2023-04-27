#pragma once

#include <cmath>

class Vector {
public:
    double x;
    double y;

    Vector(double x, double y);

    Vector operator+(Vector vector2) const;

    Vector operator-(Vector vector2) const;

    double angle() const;

    double len() const;

    Vector rotate(double a) const;

};

