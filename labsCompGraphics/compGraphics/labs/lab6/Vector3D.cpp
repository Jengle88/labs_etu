#include "Vector3D.h"

Vector3D Vector3D::operator+(const Vector3D &other) const {
    return { this->x + other.x, this->y + other.y, this->z + other.z };
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
    return { this->x - other.x, this->y - other.y, this->z - other.z  };
}

Vector3D Vector3D::operator*(const Vector3D &other) const {
    return { this->x * other.x, this->y * other.y, this->z * other.z  };
}

Vector3D Vector3D::operator/(const Vector3D &other) const {
    return { this->x / other.x, this->y / other.y, this->z / other.z  };
}
