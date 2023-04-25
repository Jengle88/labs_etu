//
// Created by evgeny on 14.04.23.
//

#include <unordered_set>
#include <set>
#include <QImage>
#include "Lab5Shaders.h"

Lab5Shaders::Lab5Shaders() = default;

void Lab5Shaders::makeWaveEffect(QImage &image, int deltaColor, int deltaPixels) {
    int cntColorSwaps = image.height() / deltaPixels;
    int deltaPixels2 = deltaPixels >> 1;
    double oneStepForColor = double(deltaColor) / deltaPixels2;
    for (int i = 0; i < cntColorSwaps; ++i) {
        for (int j = 0; j < deltaPixels; ++j) {
            int row = i * deltaPixels + j;
            int newDeltaColor = ((j <= deltaPixels2 ? j * oneStepForColor : deltaColor - (j - deltaPixels2) * oneStepForColor));
            int newDeltaForChannels = (i % 2 == 0 ? newDeltaColor : -newDeltaColor);
            for (int column = 0; column < image.width(); ++column) {
                int red = qRed(image.pixel(column, row)) + newDeltaForChannels;
                int green = qGreen(image.pixel(column, row)) + newDeltaForChannels;
                int blue = qBlue(image.pixel(column, row)) + newDeltaForChannels;
                image.setPixel(column, row, qRgb(
                        validatePixelColor(red),
                        validatePixelColor(green),
                        validatePixelColor(blue)));
            }
        }
    }
}

int Lab5Shaders::validatePixelColor(int pixelColor) {
    if (pixelColor < 0) return 0;
    if (pixelColor > 255) return 255;
    return pixelColor;
}

