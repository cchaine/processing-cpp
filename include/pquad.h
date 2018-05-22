#ifndef PQUAD_H
#define PQUAD_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class PQuad {
public:
    PQuad();
    ~PQuad();
    GLuint getVao();
private:
    GLuint vao;
};

#endif
