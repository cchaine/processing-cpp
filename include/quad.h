#ifndef QUAD_H
#define QUAD_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Quad {
public:
    Quad();
    ~Quad();
    GLuint getVao();
private:
    GLuint vao;
};

#endif
