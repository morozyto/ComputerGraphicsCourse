#include "Circle.h"

Circle::Circle(double precision_radius, double precision_segments) {
    vector <double> point;
    double MAX_ANGLE = 2 * M_PI;
    double phi = 0;

    while (phi < MAX_ANGLE) {
        point.push_back( precision_radius * cos(phi) * 2 );  // x
        point.push_back( precision_radius * sin(phi) );      // y
        point.push_back(0);                                  // z
        points.push_back(point);
        point.clear();
        phi += precision_segments;
    }
}

vector<vector<double>>& Circle::getPoints() {
    return points;
}