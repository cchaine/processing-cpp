#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../core/PCSketch.h"
#include "../core/PCFunctions.h"
#include "../core/Settings.h"

class Sketch : public PCSketch{
public:
    Sketch();
    ~Sketch();
    void render();
    void update();
    void key_callback(int key, int scancode, int action, int mode);
};

