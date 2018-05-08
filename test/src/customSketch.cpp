#include "customSketch.h"

CustomSketch::CustomSketch(int width, int height) : Sketch(width, height) {

}

void CustomSketch::setup() {
}

void CustomSketch::draw() {
    background(50);
    fill(255, 155, 155);
}

void CustomSketch::keyEvent(int key, int action) {
}
