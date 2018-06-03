#include "pline.h"

PLine::PLine() {
    float vertices[] = { 
        -1.0, 0.0,
        -1.0, 0.0,
        1.0, 0.0,
        1.0, 0.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    float normals[] = {
        0.0, -1.0,
        0.0, 1.0,
        0.0, -1.0,
        0.0, 1.0
    };

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint nbo;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

}

PLine::~PLine() {

}

GLuint PLine::getVao() {
    return this->vao;
}
