#version 330 core

in vec3 color;
out vec4 out_color;

uniform vec3 fillColor;

void main() {
    out_color = vec4(fillColor, 1.0);
}
