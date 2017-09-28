#pragma once

#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <time.h>
#include <string>

#include "PCQuad.h"
#include "PCShaderProgram.h"
#include "../PImage.h"
#include "PCTriangle.h"

#include <time.h>

PImage* loadImage(std::string path);
void frameRate(int value);
void background(int r, int g, int b);
void rect(int x, int y, int width, int height);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
void image(PImage* texture, int x, int y, int width, int height);
void image(PImage* texture, int x, int y, const short preferredSize, int value);
void image(PImage* texture, int x, int y);
int randInt(int right);
int randInt(int left, int right);
void rectMode(int value);
void imageMode(int value);
void fill(int r, int g, int b);
void fill(int value);
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
void lineWeight(int value);
void line(float x1, float y1, float x2, float y2);
int day();
int hour();
int minute();
int month();
int second();
int year();
