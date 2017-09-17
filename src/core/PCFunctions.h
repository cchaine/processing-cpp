#pragma once

#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <time.h>
#include <string>

#include "PCQuad.h"
#include "PCShaderProgram.h"
#include "../PImage.h"
#include "PCTriangle.h"

PImage* loadImage(std::string path);
void frameRate(int value);
void background(int r, int g, int b);
void rect(int x, int y, int width, int height);
void triangle(float a1, float a2, float b1, float b2, float c1, float c2);
void image(PImage* texture, int x, int y, int width, int height);
void image(PImage* texture, int x, int y, const short preferredSize, int value);
void image(PImage* texture, int x, int y);
int randInt(int right);
int randInt(int left, int right);
void rectMode(int value);
void imageMode(int value);
void fillColor(int r, int g, int b);
void fillColor(int value);
void noLoop();
float map(float value, float start1, float stop1, float start2, float stop2);
void pushMatrix();
void popMatrix();
void resetMatrix();
void translate(float x, float y);
void rotate(float angle);
void angleMode(int value);
void resetTranslation();
void resetRotation();
void beginShape();
void vertex(float x, int y);
void endShape();