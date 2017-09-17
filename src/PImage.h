#pragma once

#include <GL/glew.h>

class PImage {
public:
    PImage(GLuint textureID, int originalWidth, int originalHeight);
    int getOriginalWidth();
    int getOriginalHeight();
    GLuint getTextureID();
    int getHeightFromPreferredWidth(int width);
    int getWidthFromPreferredHeight(int height);

private:
    int originalWidth, originalHeight;
    GLuint textureID;
};