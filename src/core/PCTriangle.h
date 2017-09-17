#pragma once

#include <GL/glew.h>

class PCTriangle {
public:
    PCTriangle(float vertices[]);

    GLuint getVao();
private:
    GLuint vao, vbo;
};