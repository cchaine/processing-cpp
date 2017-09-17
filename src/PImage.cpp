#include "PImage.h"

PImage::PImage(GLuint textureID, int originalWidth, int originalHeight) {
    this->textureID = textureID;
    this->originalWidth = originalWidth;
    this->originalHeight = originalHeight;
}

GLuint PImage::getTextureID() {
    return this->textureID;
}

int PImage::getOriginalWidth() {
    return this->originalWidth;
}

int PImage::getOriginalHeight() {
    return this->originalHeight;
}

int PImage::getHeightFromPreferredWidth(int width) {
    float aspectRatio = (float)this->getOriginalHeight() / (float)this->getOriginalWidth();
    int height = int(aspectRatio * width);
    return height;
}

int PImage::getWidthFromPreferredHeight(int height) {
    float aspectRatio = (float)this->getOriginalWidth() / (float)this->getOriginalHeight();
    int width = int(aspectRatio * height);
    return width;
} 