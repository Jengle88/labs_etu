#pragma once
#include <QOpenGLFunctions>
#include <cmath>
#include "labs/lab6/Vector2D.h"
#include "labs/lab6/Vector3D.h"

class Painter {
public:
    static void wheel(double a, double b, double c);

    static void button(double a1, double b1, double c1, double a2, double b2, double c2);

    static void doorhandle(double a1, double b1, double c1, double a2, double b2, double c2);

    static void sandClock(double a, double b, double c);

    static void systemCoordinates();
};
