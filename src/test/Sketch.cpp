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
    rectMode(CORNER);
    angleMode(DEGREES);
    lineWeight(5);
    
    float a[] = {MOUSEX, MOUSEY};
    float b[] = {WIDTH / 2, HEIGHT / 2};
    glm::vec2 vect = glm::vec2(b[0] - a[0], b[1] - a[1]);
    glm::vec2 vectN = glm::normalize(vect);
    glm::vec2 ex = glm::vec2(0, 1);
    float angle = acos(glm::dot(vectN, ex))*180/PI;

    float length = glm::length(vect);
    translate(a[0], a[1]);
    if(vect.x < 0){
      rotate(-angle+90);
      length *= -1;
    }else{
      rotate(angle - 90);
    }
    rect(0, 0, length, LINEWEIGHT);
}

void Sketch::key_callback(int key, int scancode, int action, int mode) {
    
}
