#include "Sketch.h"

Sketch::Sketch() {
}

Sketch::~Sketch() {
    
}

void Sketch::update() {
}

void Sketch::render() {
    background(255, 255, 255);
    fillColor(255, 0, 0);
    angleMode(DEGREES);
    translate(WIDTH / 2, HEIGHT / 2);
    rotate(map(MOUSEX, 0, WIDTH, 0, 180));
    triangle(0, 0, 50, 0, 25, 50);
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}