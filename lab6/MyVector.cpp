//
// Created by Tony Morozov on 18.05.2018.
//

#include "MyVector.h"

MyVector::MyVector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
};

MyVector operator+(const MyVector& left, const MyVector& right) {
    double x = left.getX() + right.getX();
    double y = left.getY() + right.getY();
    double z = left.getZ() + right.getZ();
    return {x, y, z};
};

MyVector operator*(double t, const MyVector& v) {
    double x = v.getX() * t;
    double y = v.getY() * t;
    double z = v.getZ() * t;
    return {x, y, z};
}

MyVector operator*(const MyVector& left, const MyVector& right) {
    double x = left.getX() * right.getX();
    double y = left.getY() * right.getY();
    double z = left.getZ() * right.getZ();
    return {x, y, z};
}

MyVector operator-(const MyVector &v) {
    return {-v.getX(), -v.getY(), -v.getZ()};
}

MyVector operator+(double t, const MyVector &v) {
    return {t + v.getX(), t + v.getY(), t + v.getZ()};
}

MyVector operator+(const MyVector &v, double t) {
    return {t + v.getX(), t + v.getY(), t + v.getZ()};
}

MyVector& operator+=(MyVector& left, const MyVector& right) {

    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
};

void MyVector::normalize() {
    double length = sqrt(x*x + y*y + z*z);
    x /= length;
    y /= length;
    z /= length;
};

double MyVector::getX() const {
    return x;
};

double MyVector::getY() const {
    return y;
};

double MyVector::getZ() const {
    return z;
};