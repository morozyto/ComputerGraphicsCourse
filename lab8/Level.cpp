#include "Level.h"

Level::Level(double height, double precision, double MaxHeight) {
    std::vector <double> point;
    double MAX_ANGLE = 2 * M_PI;
    double phi = 0;

    while (phi < MAX_ANGLE) {
        point.push_back( (MaxHeight - height) * cos(phi) * 2 + height ); // x
        point.push_back( (MaxHeight - height) * sin(phi) );              // y
        point.push_back( height );                                       // z
        points.push_back(point);
        point.clear();
        phi += precision;
    }
}

std::vector<std::vector<double>>& Level::getPoints() {
    return points;
}