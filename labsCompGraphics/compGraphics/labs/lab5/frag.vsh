#version 330 core

uniform sampler2D texture;

varying vec2 texc;
varying vec3 waveEffectParamsForFrag;


float validateColorChannel(float color) {
    if (color > 1) return 1.0;
    if (color < 0) return 0.0;
    return color;
}

void main() {
    // ----------- input
    int height = int(waveEffectParamsForFrag.x);
    int deltaColor = int(waveEffectParamsForFrag.y);
    int deltaPixels = int(waveEffectParamsForFrag.z);
    // -----------

    vec4 colour = texture2D(texture, texc);

    if (deltaColor <= 0 || deltaPixels <= 0) {
        gl_FragColor = colour.rgba;
        return;
    }

    int deltaPixels2 = max(deltaPixels / 2, 1);
    double oneStepForColor = double(deltaColor) / double(deltaPixels2);
    int row = int((texc.y + 1) * height);
    int j = row % deltaPixels;
    int i = row / deltaPixels;
    float newDeltaColor = float(j <= deltaPixels2 ? double(double(j) * oneStepForColor) : double(double(deltaColor) - double(j - deltaPixels2) * oneStepForColor)) / 256;
    float newDeltaForChannels = (i % 2 == 0 ? newDeltaColor : -newDeltaColor);

    float r = validateColorChannel(colour.r + newDeltaForChannels);
    float g = validateColorChannel(colour.g + newDeltaForChannels);
    float b = validateColorChannel(colour.b + newDeltaForChannels);

    gl_FragColor = vec4(r, g, b, colour.a);
}