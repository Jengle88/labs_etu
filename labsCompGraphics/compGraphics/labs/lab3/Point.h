class Point {
public:
    double x;
    double y;

    Point(double x, double y);

    bool operator < (const Point& point) const
    {
        return this->x < point.x || this->x == point.x && this->y < point.y;
    }
};
