#version 330 core

attribute vec4 vertex;
attribute vec2 texCoord;

varying vec2 texc;

void main() {
    gl_Position = vertex;
    texc = texCoord;
}