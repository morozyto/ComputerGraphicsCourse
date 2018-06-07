#include "Cube.h"

void Cube::initDataOfEdge(int index, double* data, int len) {
    glBindVertexArray(VAO[index]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[index]);
    glBufferData(GL_ARRAY_BUFFER, len, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)(3* sizeof(GLdouble)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Cube::Cube(double size) {
    this->size = size;


    double top[] = {
            size,  size,  size, 1., 1., 1.,
            size, -size,  size, 1., 1., 1.,
            -size,  size,  size, 1., 1., 1.,
            -size, -size,  size, 1., 1., 1.
    };
    double down[] = {
            size, -size, -size, 0., 0., 1.,
            size,  size, -size, 0., 0., 1.,
            -size, -size, -size, 0., 0., 1.,
            -size,  size, -size, 0., 0., 1.
    };
    double front[] = {
            size, -size,  size, 0., 1., 0.,
            size, -size, -size, 0., 1., 0.,
            -size, -size,  size, 0., 1., 0.,
            -size, -size, -size, 0., 1., 0.
    };
    double back[] = {
            -size,  size,  size, 1., 0., 0.,
            -size,  size, -size, 1., 0., 0.,
            size,  size,  size, 1., 0., 0.,
            size,  size, -size, 1., 0., 0.
    };
    double left[] = {
            -size,  size,  size, 1., 1., 0.,
            -size,  size, -size, 1., 1., 0.,
            -size, -size,  size, 1., 1., 0.,
            -size, -size, -size, 1., 1., 0.
    };
    double right[] = {
            size, -size, -size, 1., 0., 1.,
            size, -size,  size, 1., 0., 1.,
            size,  size, -size, 1., 0., 1.,
            size,  size,  size, 1., 0., 1.
    };


    VBO = new GLuint[6];
    VAO = new GLuint[6];

    glGenVertexArrays(6, VAO);
    glGenBuffers(6, VBO);

    initDataOfEdge(0, top, sizeof(top));
    initDataOfEdge(1, down, sizeof(down));
    initDataOfEdge(2, right, sizeof(right));
    initDataOfEdge(3, left, sizeof(left));
    initDataOfEdge(4, front, sizeof(front));
    initDataOfEdge(5, back, sizeof(back));
}

void Cube::draw() {

    for (int i = 0; i < 6; i++) {
        glBindVertexArray(VAO[i]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

}

Cube::~Cube() {
    glDeleteVertexArrays(6, VAO);
    glDeleteBuffers(6, VBO);
    delete[] VBO;
    delete[] VAO;
}