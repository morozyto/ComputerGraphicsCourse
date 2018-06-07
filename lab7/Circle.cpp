//
// Created by Tony Morozov on 17.05.2018.
//

#include "Circle.h"

Circle::Circle(double precision_radius, double precision_segments) {

    double MAX_ANGLE = 2 * M_PI;
    double phi = 0;

    while (phi < MAX_ANGLE) {

        double COS = cos(phi), SIN = sin(phi);
        MyVector P0(precision_radius * COS * 2, precision_radius * SIN * 3 / 2, 0);
        MyVector P1(precision_radius * COS * 3. / 2., precision_radius * SIN * 5. / 4., 0);
        MyVector P2(precision_radius * COS * 5. / 4., precision_radius * SIN * 7. / 6., 0);
        MyVector P3(precision_radius * COS, precision_radius * SIN, 0);

        points.emplace_back(P0, P1, P2, P3);
        phi += precision_segments;
    }
}

std::vector<Vertex>& Circle::getPoints() {
    return points;
}