#include "Sketch.h"

Sketch::Sketch() {
}

Sketch::~Sketch() {
    
}

void Sketch::update() {
}

void Sketch::render() {
  background(80, 80, 80);
  
  pushMatrix();
  lineWeight(4);
  fill(255, 155, 155);
  translate(WIDTH / 2, HEIGHT / 2);
  rotate(map(second(), 0, 60, 0, TWO_PI));
  line(0, 0, 0, 250);
  popMatrix();

  pushMatrix();
  lineWeight(6);
  fill(155, 255, 155);
  translate(WIDTH / 2, HEIGHT / 2);
  rotate(map(minute(), 0, 60, 0, TWO_PI));
  line(0, 0, 0, 200);
  popMatrix();

  pushMatrix();
  lineWeight(8);
  fill(155, 155, 255);
  translate(WIDTH / 2, HEIGHT / 2);
  rotate(map(hour(), 0, 12, 0, TWO_PI));
  line(0, 0, 0, 120);
  popMatrix();
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}
