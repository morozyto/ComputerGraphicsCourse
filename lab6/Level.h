//
// Created by Tony Morozov on 17.05.2018.
//

#ifndef LAB6_LEVEL_H
#define LAB6_LEVEL_H

#include <vector>
#include <cmath>
#include "Vertex.h"

/// Класс для точек, находящихся на одной и той же высоте от основания
class Level{
public:
    Level(double height, double precision, double MaxHeight);
    std::vector<Vertex>& getPoints();
private:
    std::vector<Vertex> points;
};


#endif //LAB6_LEVEL_H
