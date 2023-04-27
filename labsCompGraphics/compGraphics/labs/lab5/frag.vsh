#version 330 core

uniform sampler2D texture;

varying vec2 texc;

void main() {
    vec4 colour = texture2D(texture, texc);
    gl_FragColor = colour;
}