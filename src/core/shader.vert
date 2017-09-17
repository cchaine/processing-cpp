#version 330 core

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_texCoords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main(){
    gl_Position =  projection * model * vec4(in_position, 0.0, 1.0);
    texCoords = in_texCoords;
}
