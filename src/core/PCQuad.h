#pragma once

#include <GL/glew.h>

class PCQuad {
public:
    PCQuad();

    GLuint getVao();
private:
    GLuint vao, vbo, ebo, tbo;
};