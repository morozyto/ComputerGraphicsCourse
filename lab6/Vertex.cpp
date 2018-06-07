//
// Created by Tony Morozov on 17.05.2018.
//

#include "Vertex.h"

Vertex::Vertex() :  normal(0, 0, 0), P0(0, 0, 0), P1(0, 0, 0), P2(0, 0, 0), P3(0, 0, 0) {}

Vertex::Vertex(MyVector p0, MyVector p1, MyVector p2, MyVector p3) : normal(0, 0, 0), P0(p0), P1(p1), P2(p2), P3(p3) {

    this->x = p0.getX();
    this->y = p0.getY();
    this->z = p0.getZ();
}

double Vertex::getX() {
    return x;
}

double Vertex::getY() {
    return y;
}

double Vertex::getZ() {
    return z;
}

void Vertex::setCoords(double t) {

    MyVector P = (1 - t)*(1 - t)*(1 - t)*P0 + 3*t*(1 - t)*(1 - t)*P1 + 3*t*t*(1 - t)*P2 + t*t*t*P3;
    x = P.getX();
    y = P.getY();
    z = P.getZ();
}

void Vertex::addNormal(MyVector normal) {
    neighbour_normals.push_back(normal);
};

void Vertex::countNormal() {
    for (auto &g: neighbour_normals) {
        normal += g;
    }
    normal.normalize();
};

MyVector Vertex::getNormal() {
    return normal;
}

void Vertex::draw(int i, int k) {
    glTexCoord2d(k * stepTexX, i * stepTexY);
    glNormal3d(getNormal().getX(), getNormal().getY(), getNormal().getZ());
    glVertex3d(getX(), getY(), getZ());
}

void Vertex::drawNoNormal(int i, int k) {
    glTexCoord2d(k * stepTexX, i * stepTexY);
    glVertex3d(getX(), getY(), getZ());
}
