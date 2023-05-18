#pragma once

class Vector2D {
public:
    double x, y;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(const Vector2D& other) const;
    Vector2D operator/(const Vector2D& other) const;
};

