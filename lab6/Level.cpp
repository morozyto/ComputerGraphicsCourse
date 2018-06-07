//
// Created by Tony Morozov on 17.05.2018.
//

#include "Level.h"

Level::Level(double height, double precision, double MaxHeight) {

    double MAX_ANGLE = 2 * M_PI;
    double phi = 0;

    while (phi < MAX_ANGLE) {

        double COS = cos(phi), SIN = sin(phi);

        MyVector P0((MaxHeight - height) * COS * 2 + height, (MaxHeight - height) * SIN * 3. / 2., height);
        MyVector P1((MaxHeight - height) * COS * 3. / 2. + height / 2.0, (MaxHeight - height) * SIN * 5. / 4., height);
        MyVector P2((MaxHeight - height) * COS * 5. / 4. + height / 4.0, (MaxHeight - height) * SIN * 7. / 6., height);
        MyVector P3((MaxHeight - height) * COS, (MaxHeight - height) * SIN, height);

        points.emplace_back(P0, P1, P2, P3);
        phi += precision;
    }
}

std::vector<Vertex>& Level::getPoints() {
    return points;
}
