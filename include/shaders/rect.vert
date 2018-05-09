#version 330 core
layout (location = 0) in vec2 in_pos;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(in_pos, 0.0, 1.0);
}
