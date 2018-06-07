//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_CIRCLE_H
#define LAB6_CIRCLE_H

#include <vector>
#include "Vertex.h"
#include <cmath>

/// Класс окружности в основании (нужно при разбиении)

class Circle {
public:
    Circle(double precision_radius, double precision_segments);
    std::vector<Vertex>& getPoints();
private:
    std::vector<Vertex> points;
};

#endif //LAB6_CIRCLE_H
