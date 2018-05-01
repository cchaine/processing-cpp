#ifndef SKETCH_H
#define SKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);


class Sketch {
public:
    Sketch(int width, int height);
    virtual void run() final;

    virtual void setup(){};
    virtual void draw(){};

    virtual void background(int r, int g, int b) final;
private:
    int width, height;
    GLFWwindow * window;
};

#endif
