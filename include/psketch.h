#ifndef PSKETCH_H
#define PSKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <iostream>

#include "pshader.h"
#include "pquad.h"
#include "pcircle.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

class PSketch {
public:
    PSketch();
    ~PSketch();
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
    virtual void size(int width, int height) final;
    virtual void ellipse(int x, int y, int width, int height) final;

protected:
    int WIDTH = 100;
    int HEIGHT = 100;
    int FRAMERATE = 0;
    double MOUSEX = 0;
    double MOUSEY = 0;

private:
    GLFWwindow * window = nullptr;
    int target_fps = 60;
    glm::vec3 FILLCOLOR = glm::vec3(1.0f, 1.0f, 1.0f);
    PShader * shader = nullptr;
    PShader * pointShader = nullptr;
    PQuad * quad = nullptr;
    PCircle * circle = nullptr;
    int STROKEWEIGHT = 3;
    GLuint pointVao;
};

#endif
