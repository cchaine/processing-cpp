#include "sketch.h"

Sketch::Sketch(){
    // rand init
    srand(time(NULL));
}

Sketch::~Sketch() {
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode){
}

void Sketch::run() {
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
    
    // framerate regulation init
    float interval = 1.0 / this->target_fps;
    float previousTime = glfwGetTime();
    // fps count init
    float previousCount = glfwGetTime();
    int frameCount = 0;

    // setup
    quad = new Quad();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT), -1.0f, 1.0f);
    // rect setup
    rectProgram = new Program("/usr/local/include/processing-cpp/rect.vert", "/usr/local/include/processing-cpp/rect.frag");
    rectProgram->uniform4m("projection", projection);
    // point setup
    pointProgram = new Program("/usr/local/include/processing-cpp/point.vert", "/usr/local/include/processing-cpp/point.frag");
    pointProgram->uniform4m("projection", projection);
    // gen the vao for the point render
    glGenVertexArrays(1, &pointVao);

    this->setup();

    while (!glfwWindowShouldClose(this->window)) {
        
        this->draw();
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();

        // framerate regulation
        while(glfwGetTime() - previousTime < interval && !glfwWindowShouldClose(this->window)) {
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
    }

    glfwTerminate();
}

void Sketch::background(int r, int g, int b) {
    glClearColor(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Sketch::background(int c) {
    background(c, c, c);
}

void Sketch::frameRate(int frameRate) {
    this->target_fps = frameRate;
}

void Sketch::fill(int r, int g, int b) {
    this->FILLCOLOR = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}

void Sketch::rect(int x, int y, int width, int height) { 
    rectProgram->bind();
    rectProgram->uniform3f("fillColor", this->FILLCOLOR);

    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x, y, 0));
    model = glm::rotate(model, 0.0f, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(width/2, height/2, 1));
    rectProgram->uniform4m("model", model);

    glBindVertexArray(quad->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    rectProgram->unbind();
}

void Sketch::noLoop() {
    frameRate(0);
}

void Sketch::point(int x, int y) {
    pointProgram->uniform1i("strokeWeight", this->STROKEWEIGHT);
   
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x, y, 0));
    pointProgram->uniform4m("model", model);
    
    pointProgram->bind();
    glBindVertexArray(pointVao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    pointProgram->unbind();
}

void Sketch::strokeWeight(int value) {
    this->STROKEWEIGHT = value;
}

void Sketch::size(int width, int height) {
    if(this->window == nullptr) {
        this->WIDTH = width;
        this->HEIGHT = height;
    }else{
        std::cerr << "ERROR::SKETCH::SIZE SHOULD BE CALLED FROM THE SKETCH CONSTRUCTOR" << std::endl;
    }
}
