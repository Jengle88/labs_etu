#pragma once
#include <cmath>
#include <vector>
#include "labs/lab3/Point.h"
#include <QOpenGLBuffer>


class Lab4Spline {
public:
    static void drawCurve(const std::vector<Point> &curve, double smoothBorder);

private:
    static void drawSegments(const std::vector<Point> &curve);

    static bool isFlat(const std::vector<Point> &curve, double border = 5);

    static std::vector<std::vector<Point>> subdivide(const std::vector<Point> &curve);

    static std::vector<Point> midpoints(const std::vector<Point> &points);

    static Point midpoint(const Point &point1, const Point &point2);
};
