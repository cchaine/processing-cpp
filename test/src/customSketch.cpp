#include "customSketch.h"

CustomSketch::CustomSketch() : Sketch() {
    size(800, 600);
}

void CustomSketch::setup() {
}

void CustomSketch::draw() {
    background(255);
    for(int i = 0; i < 10000; i++) {
        point(rand() % WIDTH, rand() % HEIGHT);
    }
}

void CustomSketch::keyEvent(int key, int action) {
}
