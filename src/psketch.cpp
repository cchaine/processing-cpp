#include "psketch.h"

PSketch* thisPointerForCallback;
PSketch::PSketch(){
    // rand init
    srand(time(NULL));

    thisPointerForCallback = this;
}

PSketch::~PSketch() {
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode){
    thisPointerForCallback->keyEvent(key, action);
}

void PSketch::run() {
    if(!glfwInit()) {
        exit(-1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(this->WIDTH, this->HEIGHT, "processing-cpp", nullptr, nullptr);
    glfwMakeContextCurrent(this->window);
    glfwSetKeyCallback(this->window, key_callback);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    int widthW, heightW;
    glfwGetFramebufferSize(this->window, &widthW, &heightW);
    glViewport(0, 0, widthW, heightW);
    
    // setup
    quad = new PQuad();
    circle = new PCircle();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT), -1.0f, 1.0f);
    // rect setup
    shader = new PShader("/usr/local/include/processing-cpp/main.vert", "/usr/local/include/processing-cpp/main.frag");
    shader->uniform4m((char*)"projection", projection);
    // point setup
    pointShader = new PShader("/usr/local/include/processing-cpp/point.vert", "/usr/local/include/processing-cpp/point.frag");
    pointShader->uniform4m((char*)"projection", projection);
    // gen the vao for the point render
    glGenVertexArrays(1, &pointVao);

    this->setup();
    
    // framerate regulation init
    float interval = 1.0 / this->target_fps;
    float previousTime = glfwGetTime();
    // fps count init
    float previousCount = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(this->window)) {
        glfwGetCursorPos(window, &MOUSEX, &MOUSEY);
        MOUSEY = HEIGHT - MOUSEY;
        
        this->draw();

        //Reset matrix
        if(TRANSLATE_STACK.size() != 0) {
            std::cerr << "ERROR::SKETCH::A MATRIX WAS NOT POPED AT THE END OF THE DRAW FUNCTION" << std::endl;
            exit(-1);
        }

        this->TRANSLATE.x = 0;
        this->TRANSLATE.y = 0;
        this->ROTATE = 0;
        this->SCALE.x = 1;
        this->SCALE.y = 1;
        this->TRANSLATE_STACK.clear();
        this->ROTATE_STACK.clear();
        this->SCALE_STACK.clear();
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();

        // framerate regulation
        while(glfwGetTime() - previousTime < interval && !glfwWindowShouldClose(this->window) && !needRedraw) {
            glfwPollEvents();
        }
        previousTime = glfwGetTime();
    
        // fps count
        frameCount++;
        if(glfwGetTime() - previousCount > 1.0) {
            this->FRAMERATE = frameCount;
            previousCount = glfwGetTime();
            frameCount = 0;
        }
        
        //Resets the redraw flag
        needRedraw = false;
    }

    glfwTerminate();
}

void PSketch::background(int r, int g, int b) {
    glClearColor(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PSketch::background(int c) {
    background(c, c, c);
}

void PSketch::frameRate(int frameRate) {
    this->target_fps = frameRate;
}

void PSketch::fill(int r, int g, int b) {
    if(COLORMODE == HSB) {
        glm::vec3 hsb = HSBtoRGB(r, g, b);
        this->FILLCOLOR = glm::vec3(float(hsb.r) / 255.0, float(hsb.g) / 255.0, float(hsb.b) / 255.0);
    } else {
        this->FILLCOLOR = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
    }
}

void PSketch::fill(int c) {
    if(COLORMODE != HSB) {
        fill(c, c, c);
    } else {
        std::cerr << "ERROR::SKETCH::CANNOT USE 1 VALUE FOR A HSB COLOR" << std::endl;
        exit(-1);
    }
}

void PSketch::rect(int x, int y, int width, int height) { 
    shader->bind();
    shader->uniform3f((char*)"fillColor", this->FILLCOLOR);

    glm::mat4 model = genModelMat(x + RECTMODE*(width / 2), y - RECTMODE*(width / 2), width, height);
    shader->uniform4m((char*)"model", model);

    glBindVertexArray(quad->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader->unbind();
}

void PSketch::noLoop() {
    frameRate(0);
}

void PSketch::point(int x, int y) {
    pointShader->uniform1i((char*)"strokeWeight", this->STROKEWEIGHT);
    pointShader->uniform3f((char*)"stroke", this->STROKE);
   
    glm::mat4 model = genModelMat(x, y, 0, 0);
    pointShader->uniform4m((char*)"model", model);
    
    pointShader->bind();
    glBindVertexArray(pointVao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    pointShader->unbind();
}

void PSketch::strokeWeight(int value) {
    this->STROKEWEIGHT = value;
}

void PSketch::size(int width, int height) {
    if(this->window == nullptr) {
        this->WIDTH = width;
        this->HEIGHT = height;
    }else{
        std::cerr << "ERROR::SKETCH::SIZE SHOULD BE CALLED FROM THE SKETCH CONSTRUCTOR" << std::endl;
        exit(-1);
    }
}

void PSketch::ellipse(int x, int y, int width, int height) {
    shader->bind();
    shader->uniform3f((char*)"fillColor", this->FILLCOLOR);

    glm::mat4 model = genModelMat(x + ELLIPSEMODE*(width / 2), y - ELLIPSEMODE*(height / 2), width, height);
    shader->uniform4m((char*)"model", model);

    glBindVertexArray(circle->getVao());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
    glBindVertexArray(0);
    shader->unbind();
}

void PSketch::translate(float x, float y) {
    this->TRANSLATE.x += x;
    this->TRANSLATE.y += y;
}

void PSketch::rotate(float angle) {
    this->ROTATE += angle;
}

void PSketch::scale(float xRate, float yRate) {
    this->SCALE.x += xRate;
    this->SCALE.y += yRate;
}

void PSketch::scale(float rate) {
    scale(rate, rate);
}

glm::mat4 PSketch::genModelMat(int x, int y, int width, int height) {
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x + TRANSLATE.x, y + TRANSLATE.y, 0));
    model = glm::rotate(model, ROTATE, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3((width / 2) * SCALE.x, (height / 2) * SCALE.y, 1));
    return model;
}

void PSketch::pushMatrix() {
    TRANSLATE_STACK.push_back(TRANSLATE);
    ROTATE_STACK.push_back(ROTATE);
    SCALE_STACK.push_back(SCALE);
}

void PSketch::popMatrix() {
    if(TRANSLATE_STACK.size() == 0) {
        std::cerr << "ERROR::SKETCH::PUSHMATRIX SHOULD BE CALLED BEFORE POPMATRIX" << std::endl;
        exit(-1);
    }
    TRANSLATE = TRANSLATE_STACK.back();
    TRANSLATE_STACK.pop_back();
    ROTATE = ROTATE_STACK.back();
    ROTATE_STACK.pop_back();
    SCALE = SCALE_STACK.back();
    SCALE_STACK.pop_back();
}

void PSketch::ellipseMode(int mode) {
    if(mode == CENTER || mode == CORNER) {
        ELLIPSEMODE = mode;
    } else {
        std::cerr << "ERROR::SKETCH::THIS IS NOT A VALID ELLIPSEMODE" << std::endl;
        exit(-1);
    }
}

void PSketch::rectMode(int mode) {
    if(mode == CENTER || mode == CORNER) {
        RECTMODE = mode;
    } else {
        std::cerr << "ERROR::SKETCH::THIS IS NOT A VALID RECTMODE" << std::endl;
        exit(-1);
    }
}

void PSketch::colorMode(int mode) {
    if(mode == HSB || mode == RGB) {
        this->COLORMODE = mode;
    } else {
        std::cerr << "ERROR::SKETCH::THIS IS NOT A VALID COLORMODE" << std::endl;
        exit(-1);
    }
}

glm::vec3 PSketch::HSBtoRGB(int h, int s, int b) {
    glm::vec3 rgb;
    glm::vec3 hsb = glm::vec3(float(h) / 255.0, float(s) / 255.0, float(b) / 255.0);

    int i = floor(hsb.r * 6);
    float f = hsb.r * 6 - i;
    float p = hsb.b * (1 - hsb.g);
    float q = hsb.b * (1 - f * hsb.g);
    float t = hsb.b * (1 - (1 - f) * hsb.g);

    switch(i % 6){
        case 0: rgb.r = hsb.b, rgb.g = t, rgb.b = p; break;
        case 1: rgb.r = q, rgb.g = hsb.b, rgb.b = p; break;
        case 2: rgb.r = p, rgb.g = hsb.b, rgb.b = t; break;
        case 3: rgb.r = p, rgb.g = q, rgb.b = hsb.b; break;
        case 4: rgb.r = t, rgb.g = p, rgb.b = hsb.b; break;
        case 5: rgb.r = hsb.b, rgb.g = p, rgb.b = q; break;
    }
    rgb.r *= 255;
    rgb.g *= 255;
    rgb.b *= 255;
    return rgb;
}

void PSketch::stroke(int r, int g, int b) {
    if(COLORMODE == HSB) {
        glm::vec3 hsb = HSBtoRGB(r, g, b);
        this->STROKE = glm::vec3(float(hsb.r) / 255.0, float(hsb.g) / 255.0, float(hsb.b) / 255.0);
    } else {
        this->STROKE = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
    }
}

void PSketch::noCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void PSketch::cursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void PSketch::redraw() {
    needRedraw = true;
}
