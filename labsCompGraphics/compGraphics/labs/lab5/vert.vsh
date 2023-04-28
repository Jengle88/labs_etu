#version 330 core

attribute vec4 vertex;
attribute vec2 texCoord;
uniform vec3 waveEffectParams;

varying vec2 texc;
varying vec3 waveEffectParamsForFrag;

void main() {
    gl_Position = vertex;
    texc = texCoord;
    waveEffectParamsForFrag = waveEffectParams;
}