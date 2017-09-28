#include "Sketch.h"

Sketch::Sketch() {
}

Sketch::~Sketch() {
    
}

void Sketch::update() {
}

void Sketch::render() {
  background(255, 255, 255);
  fill(0);
  lineWeight(5);

  rectMode(CENTER);
  rect(MOUSEX+200, MOUSEY, 100, 100);

  pushMatrix();
  rotate(map(MOUSEX, 0, WIDTH, 0, PI/2));
  line(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT);
  popMatrix();

  rect(MOUSEX - 200, MOUSEY, 100, 100);
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}
