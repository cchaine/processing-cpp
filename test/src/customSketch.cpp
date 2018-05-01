#include "customSketch.h"

CustomSketch::CustomSketch(int width, int height) : Sketch(width, height) {

}

int r, g, b;

void CustomSketch::setup() {
    r = g = b = 0;
}

void CustomSketch::draw() {
    r += 1;
    if(r > 255) {
        r = 0;
    }
    g += 2;
    if(g > 255) {
        g = 0;
    }
    b += 4;
    if(b > 255) {
        b = 0;
    }
    background(r, g, b);
}
