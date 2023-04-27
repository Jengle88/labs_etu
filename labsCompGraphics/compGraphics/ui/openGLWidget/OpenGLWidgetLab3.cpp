//
// Created by evgeny on 09.03.23.
//

#include <queue>
#include <unordered_set>
#include <set>
#include "OpenGLWidgetLab3.h"
#include "labs/lab1/Lab1Primitives.h"


OpenGLWidgetLab3::OpenGLWidgetLab3(QWidget *parent): QOpenGLWidget(parent) {}

void OpenGLWidgetLab3::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidgetLab3::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgetLab3::paintGL() {
    Lab1Primitives::clear();
    const double delta2X = 0.43;
    const double delta2Y = 0.5837;

    std::vector<Point> pointsForFractal;
    if (deep > 0) {
        pointsForFractal.emplace_back(Point(xCenter, yCenter));
    }
    int currIndex = 0;
    for (int i = 2; i <= deep; ++i) {
        auto newPoints = std::set<Point>();
        for (int j = currIndex; j < pointsForFractal.size(); ++j) {
            auto vectorOfNewCenters = Lab3Fractals::calcNewCenters(pointsForFractal[j].x, pointsForFractal[j].y,
                                                                   delta2X, delta2Y);
            for (const auto& newCenter : vectorOfNewCenters) {
                newPoints.insert(newCenter);
            }
        }
        currIndex += pointsForFractal.size();
        for (const auto& point: newPoints) {
            pointsForFractal.push_back(point);
        }
    }
    for(const auto& point : pointsForFractal) {
        drawFractal(point.x, point.y);
    }
}

void OpenGLWidgetLab3::drawFractal(double xCenter, double yCenter) {
    drawStars(xCenter, yCenter);
    drawWhiteLines(xCenter, yCenter);
    drawSmallRedPolygon(xCenter, yCenter);
    drawWhiteStarCenter(xCenter, yCenter);
}

void OpenGLWidgetLab3::drawStars(double xCenter, double yCenter) {
    double radius = 0.31;
    Vector fromCenter = Vector(0, radius);
    glLineWidth(3.0f);

    for (int i = 0; i < 10; ++i) {
        double angle = 2 * M_PI / 10 * i;
        auto currVector = fromCenter.rotate(angle);
        Lab3Fractals::drawLittleStar(xCenter + currVector.x, yCenter + currVector.y, 0.06, M_PI - angle);
    }

    double deltaX = 0.43;
    double deltaY = 0.065;
    Lab3Fractals::drawLittleStar(xCenter + deltaX, yCenter + deltaY, 0.065);
    Lab3Fractals::drawLittleStar(xCenter - deltaX, yCenter + deltaY, 0.065);
    Lab3Fractals::drawLittleStar(xCenter + deltaX, yCenter - deltaY, 0.065, M_PI);
    Lab3Fractals::drawLittleStar(xCenter - deltaX, yCenter - deltaY, 0.065, M_PI);
}

void OpenGLWidgetLab3::drawWhiteLines(double xCenter, double yCenter) {
    glColor4f(1.0, 1.0, 1.0, 1);
    glLineWidth(3.0f);

    std::vector<std::vector<Point>> lines = {
            { Point(-0.0101, 0.4361), Point(-0.077, 0.24), Point(-0.1945, 0.313) },
            { Point(-0.2367, 0.2787), Point(-0.209, 0.153), Point(-0.427, 0.151) },
            { Point(-0.113, 0.372), Point(0, 0.369) },
            { Point(-0.4294, 0.1436), Point(-0.256, 0) },
            { Point(-0.314, 0.2168), Point(-0.386, 0) },
            { Point(0.0018, 0.128), Point(-0.029, 0.192), Point(-0.275, 0.199), Point(-0.195, -0.042) },
            { Point(0.0018, 0.128), Point(-0.021, 0.057), Point(-0.132, 0.136), Point(-0.332, 0) },
            { Point(0.097, 0.162), Point(-0.1, 0.315), Point(-0.185, 0.076), Point(-0.079, 0) },
            { Point(0, 0.24), Point(-0.099, 0.161), Point(-0.059, 0.04), Point(-0.196, 0.035), Point(-0.2718, -0.1856) },
    };
    Lab3Fractals::drawLines(lines, 1, 1, xCenter, yCenter);
    Lab3Fractals::drawLines(lines, -1, 1, xCenter, yCenter);
    Lab3Fractals::drawLines(lines, 1, -1, xCenter, yCenter);
    Lab3Fractals::drawLines(lines, -1, -1, xCenter, yCenter);
}

void OpenGLWidgetLab3::drawSmallRedPolygon(double xCenter, double yCenter) {
    glColor4f(1.0, 0.0, 0.0, 1);
    glLineWidth(3.0f);

    std::vector<std::vector<Point>> polygons = {
            { Point(-0.0981, 0.3077), Point(-0.066, 0.2823), Point(-0.08, 0.2476), Point(-0.1128, 0.27) },
            { Point(-0.2705, 0.1968), Point(-0.2264, 0.1954), Point(-0.2137, 0.1567), Point(-0.2572, 0.1574) },
            { Point(-0.326, 0), Point(-0.2946, 0.0203), Point(-0.2625, 0), Point(-0.2966, -0.0217) },

            { Point(0, 0.2317), Point(-0.05, 0.2), Point(-0.0246, 0.1943), Point(0.0021, 0.1364), Point(0.022, 0.1918), Point(0.0388, 0.2018) },
            { Point(-0.1393, 0.1881), Point(-0.1686, 0.1165), Point(-0.1312, 0.1395), Point(-0.0845, 0.1065), Point(-0.1025, 0.1619), Point(-0.0682, 0.1894) },
            { Point(-0.2278, 0.066), Point(-0.209, 0.008), Point(-0.1997, 0.0386), Point(-0.1393, 0.041), Point(-0.1903, 0.0735), Point(-0.1804, 0.1) },

            { Point(-0.059, 0.1885), Point(-0.093, 0.1597), Point(-0.0762, 0.1045), Point(-0.0246, 0.0645), Point(-0.0054, 0.1277), Point(-0.031, 0.186) },
            { Point(-0.1662, 0.1133), Point(-0.1809, 0.0775), Point(-0.1299, 0.043), Point(-0.066, 0.0441), Point(-0.0822, 0.0975), Point(-0.1317, 0.1312) },
            { Point(-0.2032, 0.0015), Point(-0.1909, -0.0327), Point(-0.1352, -0.0356), Point(-0.0846, 0), Point(-0.1348, 0.0302), Point(-0.1918, 0.0277) },

    };
    Lab3Fractals::drawPolygon(polygons, 1, 1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, -1, 1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, 1, -1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, -1, -1, xCenter, yCenter);
}

void OpenGLWidgetLab3::drawWhiteStarCenter(double xCenter, double yCenter) {
    glColor4f(1.0, 1.0, 1.0, 1);
    glLineWidth(3.0f);

    std::vector<std::vector<Point>> polygons = {
            { Point(0, 0), Point(0, 0.04), Point(-0.0196, 0.0567), Point(-0.0243, 0.034), Point(-0.0574, 0.0391), Point(-0.0401, 0.0118), Point(-0.08, 0) }
    };

    Lab3Fractals::drawPolygon(polygons, 1, 1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, -1, 1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, 1, -1, xCenter, yCenter);
    Lab3Fractals::drawPolygon(polygons, -1, -1, xCenter, yCenter);
}
