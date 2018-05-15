#ifndef CIRCLE_H
#define CIRCLE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Circle {
public:
    Circle();
    ~Circle();
    GLuint getVao();
private:
    GLuint vao;
    int res = 360;
};

#endif
