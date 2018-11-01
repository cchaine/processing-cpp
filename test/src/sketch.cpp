#include "sketch.h"

int t = 0;

Sketch::Sketch() : PSketch() {
    size(800, 800);
}

void Sketch::setup() {
    stroke(255, 255, 255);
}

void Sketch::draw() {
    background(242);
    for(int i = 0; i < 360; i+=3) {
		float x = cos(radians(i)) * 50 + WIDTH / 2;
		float y = sin(radians(i)) * 100 + HEIGHT / 2;
		float w = sin(radians(t + i)) * 200;
		w = abs(w);

		float col = map(i, 0, 360, 0, 255);
		fill(col, col, col);

		fill(col, 0, 88);
		ellipse(x, y, w, w);
    }
    t++;
}


void Sketch::keyEvent(int key, int action) {
}
