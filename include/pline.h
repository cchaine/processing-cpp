#ifndef PLINE_H
#define PLINE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class PLine {
public:
    PLine();
    ~PLine();
    GLuint getVao();
private:
    GLuint vao;
};

#endif
