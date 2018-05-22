#ifndef CUSTOMSKETCH_H
#define CUSTOMSKETCH_H

#include "psketch.h"

class CustomSketch : public PSketch {
public:
    CustomSketch();
    void setup();
    void draw();
    void keyEvent(int key, int action);
};

#endif
