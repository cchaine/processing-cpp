#include "pshader.h"

PShader::PShader(std::string vertexPath, std::string fragmentPath) {
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
        exit(-1);
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
        exit(-1);
    }
    
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

PShader::~PShader() {

}

void PShader::bind() {
    glUseProgram(this->id);
}

void PShader::unbind() {
    glUseProgram(0);
}

void PShader::uniform3f(GLchar * uniformVariable, glm::vec3 value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void PShader::uniform4m(GLchar * uniformVariable, glm::mat4 value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void PShader::uniform1i(GLchar * uniformVariable, int value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform1i(uniformLocation, value);
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

void PShader::uniform1f(GLchar * uniformVariable, float value) {
    this->bind();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform1f(uniformLocation, value);
}

GLuint PShader::getID() {
	return this->id;	
}
