#ifndef PSKETCH_H
#define PSKETCH_H

#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <vector>
#include <cmath>

#include "pshader.h"
#include "pquad.h"
#include "pcircle.h"
#include "pline.h"

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

enum ColorMode { RGB, HSB };
enum LineMode { ROUND, BEVEL, MILTER, SQUARE };

struct PTransformations {
    glm::vec2 translate = glm::vec2(0.0f, 0.0f);
    float rotate = 0.0f;
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);
};

struct PStyle {
    glm::vec3 fillColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 stroke = glm::vec3(1.0f, 1.0f, 1.0f);
    int strokeWeight = 1;
    LineMode strokeCap = ROUND;
    LineMode strokeJoin = MILTER;
};

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
    virtual void colorMode(ColorMode mode) final;
    virtual void stroke(int r, int g, int b) final;
    virtual void noCursor() final;
    virtual void cursor() final;
    virtual void redraw() final;
    virtual void keyEvent(int key, int action) {};
    virtual void strokeCap(LineMode kind) final;
    virtual void strokeJoin(LineMode kind) final;
    virtual void pushStyle() final;
    virtual void popStyle() final;
    virtual void line(int x1, int y1, int x2, int y2) final;
    virtual float map(float value, float start1, float stop1, float start2, float stop2) final;
    virtual float radians(float degree) final;

protected:
    int WIDTH = 100;
    int HEIGHT = 100;
    int FRAMERATE = 0;
    double MOUSEX = 0;
    double MOUSEY = 0;
    const int CENTER = 0;
    const int CORNER = 1;

private:
    GLFWwindow * window = nullptr;
    int target_fps = 60;
    PShader * shader = nullptr;
    PShader * pointShader = nullptr;
    PShader * lineShader = nullptr;
    PQuad * quadObj = nullptr;
    PCircle * circleObj = nullptr;
    PLine * lineObj = nullptr;
    GLuint pointVao;
    std::vector<PTransformations> transformations_stack = std::vector<PTransformations>();
    std::vector<PStyle> style_stack = std::vector<PStyle>();
    bool needRedraw = false;

    glm::mat4 genModelMat(int x, int y, int width, int height);
    glm::vec3 HSBtoRGB(int h, int s, int b);

    PStyle style;
    PTransformations transformations;
    int RECTMODE = 1;
    int ELLIPSEMODE = 0;
    ColorMode COLORMODE = RGB;
};

#endif
