#include "program.h"

Program::Program(std::string vertexPath, std::string fragmentPath) {
    std::string vertexCodeStr = load(vertexPath);
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

    std::string fragmentCodeStr = load(fragmentPath);
    const char* fragmentCode = fragmentCodeStr.c_str();
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Program::~Program() {

}

void Program::bind() {
    glUseProgram(this->id);
}

void Program::unbind() {
    glUseProgram(0);
}

void Program::uniform3f(GLchar * uniformVariable, glm::vec3 value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void Program::uniform4m(GLchar * uniformVariable, glm::mat4 value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
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
