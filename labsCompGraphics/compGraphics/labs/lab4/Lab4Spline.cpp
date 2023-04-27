//
// Created by evgeny on 31.03.23.
//

#include "Lab4Spline.h"

Point Lab4Spline::midpoint(const Point &point1, const Point &point2) {
    return {(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
}

std::vector<Point> Lab4Spline::midpoints(const std::vector<Point> &points) {
    std::vector<Point> midpointArray(points.size() - 1);
    for (int i = 0; i < midpointArray.size(); ++i) {
        midpointArray[i] = midpoint(points[i], points[i+1]);
    }
    return midpointArray;
}

std::vector<std::vector<Point>> Lab4Spline::subdivide(const std::vector<Point> &curve) {
    auto midpoint1 = midpoints(curve);
    auto midpoint2 = midpoints(midpoint1);
    auto midpoint3 = midpoints(midpoint2);
    auto midpoint4 = midpoints(midpoint3);
    auto midpoint5 = midpoints(midpoint4);

    return {{curve[0], midpoint1[0], midpoint2[0], midpoint3[0], midpoint4[0], midpoint5[0]},
            {midpoint5[0], midpoint4[1], midpoint3[2], midpoint2[3], midpoint1[4], curve[5]}};
}

void Lab4Spline::drawCurve(const std::vector<Point> &curve, double smoothBorder) {
    if (isFlat(curve, smoothBorder)) {
        drawSegments(curve);
    } else {
        auto pieces = subdivide(curve);
        drawCurve(pieces[0], smoothBorder);
        drawCurve(pieces[1], smoothBorder);
    }
}

bool Lab4Spline::isFlat(const std::vector<Point> &curve, double border) {
    double ax = pow(-4.0 * curve[0].x + 5.0 * curve[1].x - curve[5].x, 2.0);
    double ay = pow(-4.0 * curve[0].y + 5.0 * curve[1].y - curve[5].y, 2.0);
    double bx = pow(-6.0 * curve[0].x + 10.0 * curve[2].x - 4.0 * curve[5].x, 2.0);
    double by = pow(-6.0 * curve[0].y + 10.0 * curve[2].y - 4.0 * curve[5].y, 2.0);
    double cx = pow(-4.0 * curve[0].x + 10.0 * curve[3].x - 6.0 * curve[5].x, 2.0);
    double cy = pow(-4.0 * curve[0].y + 10.0 * curve[3].y - 6.0 * curve[5].y, 2.0);
    double dx = pow(-curve[0].y + 5.0 * curve[4].y - 4.0 * curve[5].y, 2.0);
    double dy = pow(-curve[0].y + 5.0 * curve[4].y - 4.0 * curve[5].y, 2.0);
    return (std::max(std::max(ax, bx), std::max(cx, dx)) + std::max(std::max(ay, by), std::max(cy, dy)) <= border);
}

void Lab4Spline::drawSegments(const std::vector<Point> &curve) {
    glBegin(GL_LINE_STRIP);
    for (const auto& point : curve) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}


