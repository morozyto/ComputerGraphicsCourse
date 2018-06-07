//
// Created by Tony Morozov on 17.05.2018.
//

#include <GLFW/glfw3.h>
#include <cmath>

void make_perspective(){
    double M[] = {
            1,  0,  0,  0,
            0,  1,  0,  0,
            0,  0, -1,  0,
            0,  0, -0.42, 3.0
    };
    double phi = 1.;
    double M1[] = {
            1, 0       , 0,         0,
            0, cos(phi), -sin(phi), 0,
            0, sin(phi), cos(phi) , 0,
            0, 0       , 0,         1
    };
    phi = -0.2;
    double M2[] = {
            cos(phi), 0, sin(phi), 0,
            0, 1,        0, 0,
            -sin(phi), 0, cos(phi), 0,
            0, 0,        0, 1
    };

    glLoadMatrixd(M);
    glMultMatrixd(M1);
    glMultMatrixd(M2);
}

void make_orth_front(){
    double M[] = {
            1,  0,  0,  0,
            0,  0,  1,  0,
            0,  1,  0,  0,
            0,  0,  0,  4
    };
    glLoadMatrixd(M);
}

void make_orth_side(){
    double M[] = {
            0,  0, -1,  0,
            1,  0,  0,  0,
            0,  1,  0,  0,
            0,  0,  0,  4
    };
    glLoadMatrixd(M);
}

void make_orth_top(){
    double M[] = {
            1,  0,  0,  0,
            0,  1,  0,  0,
            0,  0, -1,  0,
            0,  0,  0,  4
    };
    glLoadMatrixd(M);
}

