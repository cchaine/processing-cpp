#include "sketch.h"

Sketch * thisPtr = nullptr;
Sketch::Sketch(int width, int height){
    this->width = width;
    this->height = height;
    thisPtr = this;
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

    this->window = glfwCreateWindow(this->width, this->height, "processing-cpp", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    glewInit();
    
    int widthW, heightW;
    glfwGetFramebufferSize(window, &widthW, &heightW);
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

    std::string vertexCodeStr = load("/usr/local/include/processing-cpp/vertex.vert");
    const char* vertexCode = vertexCodeStr.c_str();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::string fragmentCodeStr = load("/usr/local/include/processing-cpp/fragment.frag");
    const char* fragmentCode = fragmentCodeStr.c_str();
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    while (!glfwWindowShouldClose(window)) {
        this->draw();

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // framerate regulation
        while(glfwGetTime() - previousTime < interval && !glfwWindowShouldClose(window)) { 
            glfwPollEvents();
        }
        previousTime = glfwGetTime();
    
        // fps count
        frameCount++;
        if(glfwGetTime() - previousCount > 1.0) {
            this->fps = frameCount;
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

void Sketch::frameRate(int framerate) {
    this->target_fps = framerate;
}

std::string load(std::string path) {
    std::string content;
    std::ifstream fileStream(path, std::ios::in);
    if(!fileStream.is_open()) {
        std::cerr << "ERROR::FILELOADER::FILE DOESN'T EXIST" << std::endl;
        exit(-1);
    }
    std::string line = "";
    while(!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}
