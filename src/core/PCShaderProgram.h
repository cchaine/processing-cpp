#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string load(std::string path);

class PCShaderProgram {
public:
    PCShaderProgram(std::string vertexPath, std::string fragmentPath);
    void use();

    GLuint getId();
    void uniform4m(const GLchar * uniformVariable, glm::mat4 data);
    void uniform3f(const GLchar * uniformVariable, glm::vec3 data);
    void uniform4f(const GLchar * uniformVariable, glm::vec4 data);
    void uniform1i(const GLchar * uniformVariable, int data);
    
private:
    GLuint id;
};