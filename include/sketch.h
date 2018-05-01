#ifndef SKETCH_H
#define SKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

class Sketch {
public:
    Sketch();
    void start();
};

#endif
