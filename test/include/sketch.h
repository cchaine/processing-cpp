#ifndef SKETCH_H
#define SKETCH_H

#include "psketch.h"

class Sketch : public PSketch {
public:
    Sketch();
    void setup();
    void draw();
    void keyEvent(int key, int action);
};

#endif
