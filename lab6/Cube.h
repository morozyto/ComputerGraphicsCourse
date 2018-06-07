//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_CUBE_H
#define LAB6_CUBE_H

#include <GLFW/glfw3.h>

class Cube {
public:
    Cube(double size);
    void draw();
private:
    double size;
    void draw_edge(double *edge, double* colour, double* normal);
};

#endif //LAB6_CUBE_H
