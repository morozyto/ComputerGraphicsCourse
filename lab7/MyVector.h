//
// Created by Tony Morozov on 18.05.2018.
//

#ifndef LAB6_NORMAL_H
#define LAB6_NORMAL_H


#include <cmath>

class MyVector {
private:
    double x, y, z;
public:
    MyVector(double x, double y, double z);

    friend MyVector operator+(const MyVector& left, const MyVector& right);
    friend MyVector& operator+=(MyVector& left, const MyVector& right);
    friend MyVector operator*(const MyVector& left, const MyVector& right);
    friend MyVector operator*(double t, const MyVector& v);
    friend MyVector operator-(const MyVector& v);
    friend MyVector operator+(double t, const MyVector& v);
    friend MyVector operator+(const MyVector& v, double t);

    void normalize();

    double getX() const;
    double getY() const;
    double getZ() const;

    double* getVec();
};


#endif //LAB6_NORMAL_H
