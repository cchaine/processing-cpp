#include "sketch.h"

Sketch::Sketch() : PSketch() {
    size(800, 600);
}

void Sketch::setup() {
}

void Sketch::draw() {
    background(50);
    rectMode(CENTER);
    pushMatrix();
    pushStyle();
    fill(255, 155, 155);
    rotate(45);
    translate(50, 50);
    rect(MOUSEX, MOUSEY, 50, 50);
    popStyle();
    popMatrix();
    rect(MOUSEX, MOUSEY, 50, 50);
}

void Sketch::keyEvent(int key, int action) {
}
