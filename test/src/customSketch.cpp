#include "customSketch.h"

CustomSketch::CustomSketch() : Sketch() {
    size(800, 600);
}

void CustomSketch::setup() {
}

int r = 0;
void CustomSketch::draw() {
    background(50);
    fill(255, 155 + 40*sin(float(r) / 10.0), 155);
    ellipse(MOUSEX, MOUSEY, 100 + 50*sin(float(r) / 10.0), 100 + 50*sin(float(r) / 10.0));
    r++;
}

void CustomSketch::keyEvent(int key, int action) {
}
