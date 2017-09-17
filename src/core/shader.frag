#version 330 core

in vec2 texCoords;

out vec4 color;

uniform vec3 fillColor;
uniform int isTex;
uniform sampler2D tex;

void main() {
    if(isTex == 0){
        color = vec4(fillColor, 1.0);
    }else{
        color = texture(tex, texCoords);
    }
}