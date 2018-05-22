#include "pcircle.h"

PCircle::PCircle() {
    float vertices[2*res+2];
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    for(int i = 0; i < res; i++) {
        vertices[2+2*i] = cos(i);
        vertices[2+2*i+1] = sin(i);
    }
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

PCircle::~PCircle() {

}

GLuint PCircle::getVao() {
    return vao;
}


