#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_norm;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(in_pos + in_norm, 0, 1);
}
