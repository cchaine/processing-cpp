#ifndef CUSTOMSKETCH_H
#define CUSTOMSKETCH_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sketch.h"

class CustomSketch : public Sketch {
public:
    CustomSketch(int width, int height);
    void setup();
    void draw();
};

#endif
