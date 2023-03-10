#include <QOpenGLBuffer>
#include "Lab3Fractals.h"

void Lab3Fractals::drawFractal(double x, double y, double radius, double angle, int deep) {
    double pi5 = M_PI / 5;
    double h = 2 * radius * cos(pi5);
    for (int i = 0; i < 5; ++i) {
        double ang2 = angle + pi5 * i * 2;
        double x2 = x - h * cos(ang2);
        double y2 = y - h * sin(ang2);
        double rad2 = radius / (2 * cos(pi5) + 1);
        double ang3 = angle + M_PI + (2 * i + 1) * pi5;
        for (int j = 0; j < 4; ++j) {
            glVertex2f(x + rad2 * cos(ang3 + j * pi5 * 2), y + rad2 * sin(ang3 + j * pi5 * 2));
            glVertex2f(x + rad2 * cos(ang3 + (j + 1) * pi5 * 2), y + rad2 * sin(ang3 + (j + 1) * pi5 * 2));
        }
        if (deep > 0) drawFractal(x2, y2, radius / (2 * cos(pi5) + 1), angle + M_PI + (2 * i + 1) * pi5, deep - 1);
    }
}
