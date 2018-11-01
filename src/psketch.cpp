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
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT), -1.0f, 1.0f);
    // rect setup
    shader = new PShader("/usr/local/include/processing-cpp/main.vert", "/usr/local/include/processing-cpp/main.frag");
    shader->uniform4m((char*)"projection", projection);
    quadObj = new PQuad();
    
    circleObj = new PCircle();
    // point setup
    pointShader = new PShader("/usr/local/include/processing-cpp/point.vert", "/usr/local/include/processing-cpp/point.frag");
    pointShader->uniform4m((char*)"projection", projection);
    // line setup
    lineShader = new PShader("/usr/local/include/processing-cpp/line.vert", "/usr/local/include/processing-cpp/line.frag");
    lineShader->uniform4m((char*)"projection", projection);
    lineObj = new PLine();
    
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
        // reverts the mouseY axis
        MOUSEY = HEIGHT - MOUSEY;
        
        this->draw();

        //Reset matrix
        if(transformations_stack.size() != 0) {
            std::cerr << "ERROR::SKETCH::A MATRIX WAS NOT POPED AT THE END OF THE DRAW FUNCTION" << std::endl;
            exit(-1);
        }
		
		// resets the transformation
        this->transformations = PTransformations();
        this->transformations_stack.clear();
        
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
        this->style.fillColor = glm::vec3(float(hsb.r) / 255.0, float(hsb.g) / 255.0, float(hsb.b) / 255.0);
    } else {
        this->style.fillColor = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
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
    shader->uniform3f((char*)"fillColor", this->style.fillColor);

    glm::mat4 model = genModelMat(x + RECTMODE*(width / 2), y - RECTMODE*(width / 2), width, height);
    shader->uniform4m((char*)"model", model);

    glBindVertexArray(quadObj->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader->unbind();
}

void PSketch::noLoop() {
    frameRate(0);
}

void PSketch::point(int x, int y) {
    pointShader->uniform1i((char*)"strokeWeight", this->style.strokeWeight);
    pointShader->uniform3f((char*)"stroke", this->style.stroke);
   
    glm::mat4 model = genModelMat(x, y, 0, 0);
    pointShader->uniform4m((char*)"model", model);
    
    pointShader->bind();
    glBindVertexArray(pointVao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    pointShader->unbind();
}

void PSketch::strokeWeight(int value) {
    this->style.strokeWeight = value;
    if(value > 120) {
        this->style.strokeWeight = 120;
    }
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
    shader->uniform3f((char*)"fillColor", this->style.fillColor);

    glm::mat4 model = genModelMat(x + ELLIPSEMODE*(width / 2), y - ELLIPSEMODE*(height / 2), width, height);
    shader->uniform4m((char*)"model", model);

    glBindVertexArray(circleObj->getVao());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
    glBindVertexArray(0);
    shader->unbind();
}

void PSketch::translate(float x, float y) {
    this->transformations.translate.x += x;
    this->transformations.translate.y += y;
}

void PSketch::rotate(float angle) {
    this->transformations.rotate += angle;
}

void PSketch::scale(float xRate, float yRate) {
    this->transformations.scale.x += xRate;
    this->transformations.scale.y += yRate;
}

void PSketch::scale(float rate) {
    scale(rate, rate);
}

glm::mat4 PSketch::genModelMat(int x, int y, int width, int height) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x + transformations.translate.x, y + transformations.translate.y, 0));
    model = glm::rotate(model, transformations.rotate, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3((width / 2) * transformations.scale.x, (height / 2) * transformations.scale.y, 1));
    return model;
}

void PSketch::pushMatrix() {
    transformations_stack.push_back(transformations);
}

void PSketch::popMatrix() {
    if(transformations_stack.size() == 0) {
        std::cerr << "ERROR::SKETCH::PUSHMATRIX SHOULD BE CALLED BEFORE POPMATRIX" << std::endl;
        exit(-1);
    }
    transformations = transformations_stack.back();
    transformations_stack.pop_back();
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

void PSketch::colorMode(ColorMode mode) {
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
        this->style.stroke = glm::vec3(float(hsb.r) / 255.0, float(hsb.g) / 255.0, float(hsb.b) / 255.0);
    } else {
        this->style.stroke = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
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

void PSketch::strokeCap(LineMode kind) {
    if(kind == ROUND || kind == SQUARE) {
        this->style.strokeCap = kind;
    } else {
        std::cerr << "ERROR::SKETCH::THIS IS NOT A VALID STROKECAP" << std::endl;
        exit(-1);
    }
}

void PSketch::strokeJoin(LineMode kind) {
    if(kind == ROUND || kind == MILTER || kind == BEVEL) {
        this->style.strokeJoin = kind;
    } else {
        std::cerr << "ERROR::SKETCH::THIS IS NOT A VALID STROKEJOIN" << std::endl;
        exit(-1);
    }
}

void PSketch::pushStyle() {
    style_stack.push_back(style);
}

void PSketch::popStyle() {
    if(style_stack.size() == 0) {
        std::cerr << "ERROR::SKETCH::PUSHSTYLE SHOULD BE CALLED BEFORE POPSTYLE" << std::endl;
        exit(-1);
    }
    style = style_stack.back();
    style_stack.pop_back();
}

void PSketch::line(int x1, int y1, int x2, int y2) {
    float dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)) / 2;
    float angle = atan2(y2-y1, x2 - x1);
   
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x1, y1, 0.0));
    model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(dist, 0.0, 0.0));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(dist, float(style.strokeWeight) / 2.0, 0.0f));
    lineShader->uniform4m((char*)"model", model);

    lineShader->uniform3f((char*)"stroke", style.stroke);

    lineShader->bind();
    glBindVertexArray(lineObj->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    lineShader->unbind();
    
    if(style.strokeCap == ROUND) {
        point(x1, y1);
        point(x2, y2);
    }
}

float PSketch::map(float value, float start1, float stop1, float start2, float stop2) {
	if(start1 <= value && value <= stop1) {
		return (stop2 - start2) / (stop1 - start1) * value;	
	} else {
        std::cerr << "ERROR::MAP::VALUE BOUNDARIES ARE NOT CORRECT" << std::endl;
        exit(-1);
	}
}

float PSketch::radians(float degree) {
	return degree * M_PI / 180.0;
}
