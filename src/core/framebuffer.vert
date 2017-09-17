#version 330 core

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_texCoords;

out vec2 texCoords;

void main(){
    gl_Position =  vec4(in_position, 0.0, 1.0);
    texCoords = vec2(in_texCoords.x, 1-in_texCoords.y);
}
