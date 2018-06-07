//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_VERTEX_H
#define LAB6_VERTEX_H

#include <cmath>
#include <vector>
#include "MyVector.h"
#include <GLFW/glfw3.h>

class Vertex {
private:
    double x, y, z;
    std::vector<MyVector> neighbour_normals;
    MyVector normal;
    MyVector P0, P1, P2, P3;
    double stepTexX = 0.2, stepTexY = 0.2;

public:
    Vertex();
    Vertex(MyVector P0, MyVector P1, MyVector P2, MyVector P3);
    double getX();
    double getY();
    double getZ();

    void setCoords(double t);
    void draw(int i, int k);
    void drawNoNormal(int i, int k);
    void addNormal(MyVector normal);
    void countNormal();
    MyVector getNormal();
};

#endif //LAB6_VERTEX_H
