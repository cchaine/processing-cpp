#version 330 core

uniform mat4 model;
uniform mat4 projection;
uniform int strokeWeight;

void main() {
    gl_PointSize = strokeWeight;
    gl_Position = projection * model * vec4(0.0, 0.0, 0.0, 1.0);
}
