//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_CONE_H
#define LAB6_CONE_H

#include <vector>
#include "MyVector.h"
#include "Level.h"
#include "Circle.h"
#include <iostream>

using std::vector;

class Cone {
public:
    Cone(double MaxHeight);
    void count_points(int count_of_vertexes, int count_of_heights, double t);
    void count_animation(double t);
    void draw();
private:
    vector<Level> levels;
    vector<Circle> circles;
    Vertex top;
    double MaxHeight;
};

#endif //LAB6_CONE_H
