#ifndef PSKETCH_H
#define PSKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <vector>

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
    virtual void fill(int c) final;
    virtual void rect(int x, int y, int width, int height) final;
    virtual void point(int x, int y) final;
    virtual void strokeWeight(int value) final;
    virtual void size(int width, int height) final;
    virtual void ellipse(int x, int y, int width, int height) final;
    virtual void translate(float x, float y) final;
    virtual void rotate(float angle) final;
    virtual void scale(float xRate, float yRate) final;
    virtual void scale(float rate) final;
    virtual void pushMatrix() final;
    virtual void popMatrix() final;
    virtual void rectMode(int mode) final;
    virtual void ellipseMode(int mode) final;
    virtual void colorMode(int mode) final;
    virtual void stroke(int r, int g, int b) final;
    virtual void noCursor() final;
    virtual void cursor() final;
    virtual void redraw() final;
    virtual void keyEvent(int key, int action) {};

protected:
    int WIDTH = 100;
    int HEIGHT = 100;
    int FRAMERATE = 0;
    double MOUSEX = 0;
    double MOUSEY = 0;
    const int CENTER = 0;
    const int CORNER = 1;
    const int RGB = 0;
    const int HSB = 1;

private:
    GLFWwindow * window = nullptr;
    int target_fps = 60;
    PShader * shader = nullptr;
    PShader * pointShader = nullptr;
    PQuad * quad = nullptr;
    PCircle * circle = nullptr;
    GLuint pointVao;
    std::vector<glm::vec2> TRANSLATE_STACK = std::vector<glm::vec2>();
    std::vector<float> ROTATE_STACK = std::vector<float>();
    std::vector<glm::vec2> SCALE_STACK = std::vector<glm::vec2>();
    bool needRedraw = false;

    glm::mat4 genModelMat(int x, int y, int width, int height);
    glm::vec3 HSBtoRGB(int h, int s, int b);

    glm::vec3 FILLCOLOR = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec2 TRANSLATE = glm::vec2(0.0f, 0.0f);
    float ROTATE = 0.0f;
    glm::vec2 SCALE = glm::vec2(1.0f, 1.0f);
    int STROKEWEIGHT = 3;
    glm::vec3 STROKE = glm::vec3(1.0f, 1.0f, 1.0f);
    int RECTMODE = 1;
    int ELLIPSEMODE = 0;
    int COLORMODE = 0;
};

#endif
