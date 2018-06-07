#include "Cube.h"

Cube::Cube(double size) {
    this->size = size;
}

void Cube::draw() {
    double white[] =  { 1., 1., 1.};
    double yellow[] = { 1., 1., 0.};
    double red[] =    { 1., 0., 0.};
    double blue[] =   { 0., 0. ,1.};
    double light_blue[] = { 0., 1., 1.};
    double green[] =  { 0., 1., 0.};

    double top[] = {
             size,  size,  size,
             size, -size,  size,
            -size, -size,  size,
            -size,  size,  size
    };
    double down[] = {
              size, -size, -size,
              size,  size, -size,
             -size,  size, -size,
             -size, -size, -size
    };
    double front[] = {
               size, -size,  size,
               size, -size, -size,
              -size, -size, -size,
              -size, -size,  size
    };
    double back[] = {
             -size,  size,  size,
             -size,  size, -size,
              size,  size, -size,
              size,  size,  size
    };
    double left[] = {
             -size,  size,  size,
             -size,  size, -size,
             -size, -size, -size,
             -size, -size,  size
    };
    double right[] = {
              size, -size, -size,
              size, -size,  size,
              size,  size,  size,
              size,  size, -size
    };
    draw_edge(back, blue);
    draw_edge(front, red);
    draw_edge(left, light_blue);
    draw_edge(right, green);
    draw_edge(down, yellow);
    draw_edge(top, white);
}

void Cube::draw_edge(double* vertecies, double* colour) {
    glColor3d(colour[0], colour[1], colour[2]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertecies);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}