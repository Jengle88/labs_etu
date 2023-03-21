#include <QOpenGLBuffer>
#include <vector>
#include "Lab3Fractals.h"
#include "Vector.h"

void Lab3Fractals::drawLittleStar(double xCenter, double yCenter, double radius, double initRotate) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);

    double pi5 = 0;
    double coeffForInnerTriangle = 11. / 20;
    Vector vectorFromCenter = Vector(0, radius).rotate(initRotate);
    Vector vectorFromCenterForTriangle = (vectorFromCenter - Vector(0, radius * coeffForInnerTriangle).rotate(initRotate)).rotate(2 * M_PI / 10);

    auto startVector = vectorFromCenterForTriangle.rotate(0);
    glVertex2f(xCenter + startVector.x, yCenter + startVector.y);
    for (int i = 0; i <= 5; ++i) {
        pi5 = 2 * M_PI / 5 * i;
        auto tempVector1 = vectorFromCenter.rotate(pi5);
        auto tempVector2 = vectorFromCenterForTriangle.rotate(pi5);
        if (i % 2 == 0) {
            glVertex2f(xCenter + tempVector1.x, yCenter + tempVector1.y);
            glVertex2f(xCenter + tempVector1.x, yCenter + tempVector1.y);
            glVertex2f(xCenter + tempVector2.x, yCenter + tempVector2.y);
            glVertex2f(xCenter + tempVector2.x, yCenter + tempVector2.y);
        } else {
            glVertex2f(xCenter + tempVector1.x, yCenter + tempVector1.y);
            glVertex2f(xCenter + tempVector2.x, yCenter + tempVector2.y);
            glVertex2f(xCenter + tempVector1.x, yCenter + tempVector1.y);
            glVertex2f(xCenter + tempVector2.x, yCenter + tempVector2.y);
        }
    }
    glEnd();
}

void Lab3Fractals::drawLines(const std::vector<std::vector<Point>> &lines, int signXForPoints, int signYForPoints, double deltaX, double deltaY) {
    for (const auto& line : lines) {
        glBegin(GL_LINES);
        for (int i = 1; i < line.size(); ++i) {
            glVertex2f(line[i-1].x * signXForPoints + deltaX, line[i-1].y * signYForPoints + deltaY);
            glVertex2f(line[i].x * signXForPoints + deltaX, line[i].y * signYForPoints + deltaY);
        }
        glEnd();
    }
}

void Lab3Fractals::drawPolygon(const std::vector<std::vector<Point>> &lines, int signXForPoints, int signYForPoints,
                               double deltaX, double deltaY) {
    for (const auto& line : lines) {
        glBegin(GL_POLYGON);
        for (int i = 1; i < line.size(); ++i) {
            glVertex2f(line[i-1].x * signXForPoints + deltaX, line[i-1].y * signYForPoints + deltaY);
            glVertex2f(line[i].x * signXForPoints + deltaX, line[i].y * signYForPoints + deltaY);
        }
        glEnd();
    }
}
