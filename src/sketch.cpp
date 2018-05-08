#include "sketch.h"

//Used for the key_callback
Sketch * thisPtr = nullptr;
Sketch::Sketch(int width, int height){
    this->WIDTH = width;
    this->HEIGHT = height;
    thisPtr = this;
}

Sketch::~Sketch() {
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode){
    thisPtr->keyEvent(key, action);
    thisPtr->keyPressed = action;
    thisPtr->key = key;
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
    
    int widthW, heightW;
    glfwGetFramebufferSize(this->window, &widthW, &heightW);
    glViewport(0, 0, widthW, heightW);
    
    // call of the setup fct
    this->setup();

    // framerate regulation init
    float interval = 1.0 / this->target_fps;
    float previousTime = glfwGetTime();
    // fps count init
    float previousCount = glfwGetTime();
    int frameCount = 0;

    float vertices[] = {
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    float colors[] = {
        1.0f, 0.5f, 0.5,
        0.5f, 1.0f, 0.5f,
        0.5f, 0.5f, 1.0f,
        1.0f, 1.0f, 0.5f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    GLuint cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Program * program = new Program("/usr/local/include/processing-cpp/vertex.vert", "/usr/local/include/processing-cpp/fragment.frag");

    while (!glfwWindowShouldClose(this->window)) {
        this->draw();

        program->bind();

        program->uniform3f("fillColor", this->FILLCOLOR);
        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT), -1.0f, 1.0f);
        glm::mat4 model = glm::mat4();
        model = glm::translate(model, glm::vec3(400, 300, 0));
        model = glm::rotate(model, 0.0f, glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(150, 150, 1));

        program->uniform4m("projection", projection);
        program->uniform4m("model", model);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        program->unbind();

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
