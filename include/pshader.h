#ifndef PSHADER_H
#define PSHADER_H

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string load(std::string path);

class PShader {
    public:
        PShader(std::string vertexPath, std::string fragmentPath);
        ~PShader();

        void bind();
        void unbind();
        GLuint getID();

        void uniform3f(GLchar * uniformVariable, glm::vec3 value);
        void uniform4m(GLchar * uniformVariable, glm::mat4 value);
        void uniform1i(GLchar * uniformVariable, int value);
        void uniform1f(GLchar * uniformVariable, float value);
    private:
        GLuint id;
};

#endif
