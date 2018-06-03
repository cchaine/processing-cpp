#include "sketch.h"

Sketch::Sketch() : PSketch() {
    size(800, 600);
}

void Sketch::setup() {
    //noLoop();
}

void Sketch::draw() {
    background(50);
    stroke(155, 155, 255);
    line(WIDTH / 2, HEIGHT / 2, MOUSEX, MOUSEY);
}

void Sketch::keyEvent(int key, int action) {
}
