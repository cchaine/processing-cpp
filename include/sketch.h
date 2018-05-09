#ifndef SKETCH_H
#define SKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <iostream>

#include "program.h"
#include "quad.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

class Sketch {
public:
    Sketch(int width, int height);
    ~Sketch();
    virtual void run() final;

    virtual void setup(){};
    virtual void draw(){};

    virtual void background(int r, int g, int b) final;
    virtual void background(int c) final;
    virtual void frameRate(int frameRate) final;
    virtual void noLoop() final;
    virtual void fill(int r, int g, int b) final;
    virtual void rect(int x, int y, int width, int height);
    virtual void point(int x, int y);
    virtual void strokeWeight(int value) final;

protected:
    int WIDTH, HEIGHT;
    int FRAMERATE = 0;

private:
    GLFWwindow * window;
    int target_fps = 60;
    glm::vec3 FILLCOLOR = glm::vec3(1.0f, 1.0f, 1.0f);
    Program * rectProgram;
    Program * pointProgram;
    Quad * quad;
    int STROKEWEIGHT = 3;
    GLuint pointVao;
};

#endif
