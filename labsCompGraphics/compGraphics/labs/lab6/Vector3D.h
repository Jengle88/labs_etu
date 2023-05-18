#pragma once

class Vector3D {
public:
    double x, y, z;

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(const Vector3D& other) const;
    Vector3D operator/(const Vector3D& other) const;
};
