#pragma once

#include <QRgb>
#include <QColor>
#include "QVector"
#include <iostream>
#include "labs/lab3/Point.h"


class Lab5Shaders {
    static int validatePixelColor(int pixelColor);

public:

    Lab5Shaders();

    static void makeWaveEffect(QImage& image, int deltaColor, int deltaPixels);
};
