#include "PCSketch.h"

PCQuad* pcQuad;
PCShaderProgram* pcShaderProgram;
std::map<std::string, PCTriangle*> pcTriangles;

PCSketch::PCSketch() {
    TRANSLATE_STACK = new std::vector<glm::vec2>();
    ROTATE_STACK = new std::vector<float>();

    pcQuad = new PCQuad();

    pcShaderProgram = new PCShaderProgram("../src/core/shader.vert", "../src/core/shader.frag");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT), -1.0f, 1.0f);
    pcShaderProgram->uniform4m("projection", projection);
}

PCSketch::~PCSketch() {
    TARGET_FPS = 60;
    RECTMODE = CORNER;
    IMAGEMODE = CORNER;
    FILLCOLOR = glm::vec3(0.0, 0.0, 0.0);
    NOLOOP = false;
    LOOPING = true;
    delete(TRANSLATE_STACK);
    TRANSLATE_STACK = 0;
    delete(ROTATE_STACK);
    ROTATE_STACK = 0;
}