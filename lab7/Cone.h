//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_CONE_H
#define LAB6_CONE_H

#include "definitions.h"
#include <vector>
#include "MyVector.h"
#include "Level.h"
#include "Circle.h"
#include <iostream>

using namespace std;

class Cone {
public:
    Cone(double MaxHeight);
    void count_points(int count_of_vertexes, int count_of_heights, double t);
    void count_animation(double t);
    void draw();
    void countArrays();
private:
    vector<Level> levels;
    vector<Circle> circles;
    Vertex top;
    double MaxHeight;

    vector<double> points_side;
    vector<double> normals_side;

    vector<double> points_top;
    vector<double> normals_top;

    vector<double> points_down;
    vector<double> points_down_mid;

};

#endif //LAB6_CONE_H
