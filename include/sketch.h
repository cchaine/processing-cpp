#ifndef SKETCH_H
#define SKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
std::string load(std::string);

class Sketch {
public:
    Sketch(int width, int height);
    virtual void run() final;

    virtual void setup(){};
    virtual void draw(){};

    virtual void background(int r, int g, int b) final;
    virtual void background(int c) final;
    virtual void frameRate(int framerate) final;

    // Input
    virtual void keyEvent(int key, int action){};
    int key;
    bool keyPressed = 0;
    int PRESSED = 1;
    int RELEASED = 0;

protected:
    int width, height;
    GLFWwindow * window;
    int target_fps = 60;
    int fps = 0;
};

#endif
