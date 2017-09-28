#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <vector>
#include <math.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../test/Sketch.h"
#include "Settings.h"
#include <map>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLFWwindow* window;

PCSketch* view;

int WIDTH = 800;
int HEIGHT = 600;
int DPI = 1;
int RESX = WIDTH;
int RESY = HEIGHT;
int TARGET_FPS = 60;
double MOUSEX;
double MOUSEY;
const int CENTER = 0;
const int CORNER = 1;
int RECTMODE = CORNER;
int IMAGEMODE = CORNER;
glm::vec3 FILLCOLOR = glm::vec3(0.0, 0.0, 0.0);
bool NOLOOP = false;
const short PREFERRED_WIDTH = 0;
const short PREFERRED_HEIGHT = 1;
bool LOOPING = true;
glm::vec2 TRANSLATE = glm::vec2(0.0, 0.0);
float ROTATE = 0;
std::vector<glm::vec2> * TRANSLATE_STACK;
std::vector<float> * ROTATE_STACK;
const float PI = M_PI;
const float TWO_PI = 2.0*PI;
const int RADIANS = 0;
const int DEGREES = 1;
int ANGLEMODE = 0;
int LINEWEIGHT = 1;
std::vector<int> * RECTMODE_STACK; 

void init() {
    srand(time(NULL));

    view = new Sketch();
}

void close() {
    delete(view);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    view->key_callback(key, scancode, action, mode);
}

int main() {
    if(!glfwInit()) {
        exit(-1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "kvEngine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    glewInit();

    glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int wwidth, wheight;
    glfwGetWindowSize(window, &wwidth, &wheight);
    int fwidth, fheight;
    glfwGetFramebufferSize(window, &fwidth, &fheight);
    DPI = fwidth / wwidth;

    init();

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    GLuint framebufferTex;
    glGenTextures(1, &framebufferTex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RESX*DPI, RESY*DPI, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTex, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "ERROR::FRAMEBUFFER::FRAMEBUFFER IS NOT COMPLETE" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    PCQuad* framebufferQuad = new PCQuad();
    PCShaderProgram* framebufferProgram = new PCShaderProgram("../src/core/framebuffer.vert", "../src/core/framebuffer.frag");
    framebufferProgram->uniform1i("tex", 0);

    float interval = 1.0 / TARGET_FPS;
    float previousTime = glfwGetTime();
    float elapsedTime = 0;
    float accumulator = 0;

    float counterLast = glfwGetTime();
    int counterFrame = 0;

    while (!glfwWindowShouldClose(window)) {
        elapsedTime = glfwGetTime() - previousTime;
        previousTime = glfwGetTime();
        accumulator += elapsedTime;

        while(accumulator >= interval) {
            view->update();

            glfwGetCursorPos(window, &MOUSEX, &MOUSEY);
            MOUSEX *= DPI;
            MOUSEY = HEIGHT - MOUSEY * DPI;
            accumulator -= interval;
        }

        if(LOOPING){
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            glViewport(0, 0, RESX*DPI, RESY*DPI);
            glClear(GL_COLOR_BUFFER_BIT);
            view->render();
            RECTMODE = CORNER;
            IMAGEMODE = CORNER;
            FILLCOLOR = glm::vec3(0.0, 0.0, 0.0);
            TRANSLATE = glm::vec2(0.0, 0.0);
            ROTATE = 0;
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, WIDTH, HEIGHT);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            framebufferProgram->use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, framebufferTex);
            glBindVertexArray(framebufferQuad->getVao());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        
            glfwSwapBuffers(window);
        }
        if(NOLOOP){
            LOOPING = false;
        }
        glfwPollEvents();

        double supposedTime = previousTime + (1.0 / float(TARGET_FPS));
        while(glfwGetTime() < supposedTime) {}

        counterFrame++;
        if(glfwGetTime() - counterLast >= 1.0){
            cout << float(counterFrame) << endl;
            counterFrame = 0;
            counterLast += 1.0;
        }
    }

    close();

    glfwTerminate();
    return 0;
}
