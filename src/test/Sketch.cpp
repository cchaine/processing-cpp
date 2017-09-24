#include "Sketch.h"

Sketch::Sketch() {
}

Sketch::~Sketch() {
    
}

void Sketch::update() {
}

void Sketch::render() {
    background(255, 255, 255);
    fillColor(150, 150, 255);
    angleMode(DEGREES);
    translate(MOUSEX, MOUSEY);
    triangle(0, 0, 50, 0, 25, 50);
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}
