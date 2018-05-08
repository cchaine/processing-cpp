#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string load(std::string path);

class Program {
    public:
        Program(std::string vertexPath, std::string fragmentPath);
        ~Program();

        void bind();
        void unbind();

        void uniform3f(GLchar * uniformVariable, glm::vec3 value);
        void uniform4m(GLchar * uniformVariable, glm::mat4 value);
    private:
        GLuint id;
};

#endif
