#include "PCShaderProgram.h"

using namespace std;

PCShaderProgram::PCShaderProgram(string vertexPath, std::string fragmentPath) {
    string vertexCodeStr = load(vertexPath);
    const char* vertexCode = vertexCodeStr.c_str();
    
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    string fragmentCodeStr = load(fragmentPath);
    const char* fragmentCode = fragmentCodeStr.c_str();
    
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void PCShaderProgram::use() {
    glUseProgram(id);
}

void PCShaderProgram::uniform4m(const GLchar* uniformVariable, glm::mat4 data){
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(data));
}

void PCShaderProgram::uniform3f(const GLchar * uniformVariable, glm::vec3 data) {
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform3f(uniformLocation, data.x, data.y, data.z);
}

void PCShaderProgram::uniform4f(const GLchar * uniformVariable, glm::vec4 data) {
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
}

void PCShaderProgram::uniform1i(const GLchar * uniformVariable, int data) {
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->id, uniformVariable);
    glUniform1i(uniformLocation, data);
}

string load(string path) {
    string content;
    ifstream fileStream(path, ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Couldn't read file " << path << ". File doesn't exists." << endl;
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