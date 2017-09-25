#include "Sketch.h"

Sketch::Sketch() {
}

Sketch::~Sketch() {
    
}

void Sketch::update() {
}

void Sketch::render() {
    background(255, 255, 255);
    fillColor(255, 150, 150);
    rectMode(CENTER);
    rect(MOUSEX, MOUSEY, 100, 100);
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}
