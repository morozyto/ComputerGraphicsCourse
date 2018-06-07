//
// Created by Tony Morozov on 17.05.2018.
//

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
    double top_normal[] = { 0, 0, 1 };
    double down[] = {
            size, -size, -size,
            size,  size, -size,
            -size,  size, -size,
            -size, -size, -size
    };
    double down_normal[] = { 0, 0, -1 };
    double front[] = {
            size, -size,  size,
            size, -size, -size,
            -size, -size, -size,
            -size, -size,  size
    };
    double front_normal[] = { 0, -1, 0 };
    double back[] = {
            -size,  size,  size,
            -size,  size, -size,
            size,  size, -size,
            size,  size,  size
    };
    double back_normal[] = { 0, 1, 0 };
    double left[] = {
            -size,  size,  size,
            -size,  size, -size,
            -size, -size, -size,
            -size, -size,  size
    };
    double left_normal[] = { -1, 0, 0 };
    double right[] = {
            size, -size, -size,
            size, -size,  size,
            size,  size,  size,
            size,  size, -size
    };
    double right_normal[] = { 1, 0, 0 };
    draw_edge(back, blue, back_normal);
    draw_edge(front, red, front_normal);
    draw_edge(left, light_blue, left_normal);
    draw_edge(right, green, right_normal);
    draw_edge(down, yellow, down_normal);
    draw_edge(top, white, top_normal);
}

void Cube::draw_edge(double* vertecies, double* colour, double* normal) {
    glNormal3d(normal[0], normal[1], normal[2]);
    glColor3d(colour[0], colour[1], colour[2]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertecies);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}