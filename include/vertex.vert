#version 330 core
layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec3 in_color;

out vec3 color;

void main() {
    gl_Position = vec4(in_pos, 0.0, 1.0);
    color = in_color;
}
