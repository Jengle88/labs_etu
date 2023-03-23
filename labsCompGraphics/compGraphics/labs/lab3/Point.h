#include <cmath>

class Point {
public:
    double x;
    double y;

    Point(double x, double y);

    bool operator < (const Point& point) const
    {
        return this->x < point.x || std::abs(this->x - point.x) < 0.00001 && this->y < point.y;
    }

    bool operator == (const Point& point) const
    {
        return std::abs(this->x - point.x) < 0.00001 && std::abs(this->y - point.y) < 0.00001;
    }
};
