#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Settings.h"
#include "PCQuad.h"
#include "PCShaderProgram.h"
#include "../PImage.h"
#include "PCTriangle.h"

class PCSketch {
public:
    PCSketch();
    virtual ~PCSketch();
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void key_callback(int key, int scancode, int action, int mode){};
};