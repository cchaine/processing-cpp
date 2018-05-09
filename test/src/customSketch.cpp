#include "customSketch.h"

CustomSketch::CustomSketch(int width, int height) : Sketch(width, height) {

}

void CustomSketch::setup() {
}

void CustomSketch::draw() {
    background(255);
    fill(0, 0, 0);
    rect(100, 100, 50,50);
}

void CustomSketch::keyEvent(int key, int action) {
}
