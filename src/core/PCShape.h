#pragma once

#include <GL/glew.h>

class PCShape {
public:
    PCShape(float vertices[], float count);
    GLuint getVao();
private:
    GLuint vao, vbo;
};