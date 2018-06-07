#include "Point.h"

Point::Point() {}

Point::Point(double x, double y) : Point(x, y, true) {
}

Point::Point(double x, double y, bool state) {
    this->x = x;
    this->y = y;
    this->isDrawAfter = state;
}

double Point::GetX() {
    return x;
}

double Point::GetY() {
    return y;
}

bool Point::GetState() {
    return isDrawAfter;
}

void Point::SetX(double x) {
    this->x = x;
}

void Point::SetY(double y) {
    this->y = y;
}

void Point::SetState(bool state) {
    this->isDrawAfter = state;
}

void Point::Rotate(double phi){
    double x = GetX() * cos(phi) - GetY() * sin(phi);
    double y = GetX() * sin(phi) + GetY() * cos(phi);
    SetX(x);
    SetY(y);
}

void Point::Translate(double dx, double dy) {
    SetX(GetX() + dx);
    SetY(GetY() + dy);
}
