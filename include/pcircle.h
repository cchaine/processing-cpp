#ifndef PCIRCLE_H
#define PCIRCLE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class PCircle {
public:
    PCircle();
    ~PCircle();
    GLuint getVao();
private:
    GLuint vao;
    int res = 360;
};

#endif
