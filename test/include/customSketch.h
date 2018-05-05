#ifndef CUSTOMSKETCH_H
#define CUSTOMSKETCH_H

#include "sketch.h"

class CustomSketch : public Sketch {
public:
    CustomSketch(int width, int height);
    void setup();
    void draw();
    void keyEvent(int key, int action);
};

#endif
