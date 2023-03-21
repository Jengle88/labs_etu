#pragma once
#include <cmath>
#include "Point.h"
#include "Vector.h"

class Lab3Fractals {
public:
    static void drawLittleStar(double xCenter, double yCenter, double radius, double initRotate = 0);

    static void drawLines(const std::vector<std::vector<Point>> &lines, int signXForPoints, int signYForPoints,
                          double deltaX = 0, double deltaY = 0);

    static void drawPolygon(const std::vector<std::vector<Point>> &lines, int signXForPoints, int signYForPoints,
                            double deltaX = 0, double deltaY = 0);

    static std::vector<Point> calcNewCenters(double xCenter, double yCenter, double delta2X, double delta2Y) {
        std::vector<Point> result;
        double delta1 = 0.86;
        result.emplace_back(xCenter + delta1, yCenter);
        result.emplace_back(xCenter + delta2X, yCenter + delta2Y);
        result.emplace_back(xCenter + delta2X, yCenter - delta2Y);

        result.emplace_back(xCenter - delta1, yCenter);
        result.emplace_back(xCenter - delta2X, yCenter + delta2Y);
        result.emplace_back(xCenter - delta2X, yCenter - delta2Y);

        return result;
    }
};
