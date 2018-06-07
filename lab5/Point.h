#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
private:
    double x, y;
    bool isDrawAfter;
public:
    Point();
    Point(double x, double y);
    Point(double x, double y, bool state);
    double GetX();
    double GetY();
    bool GetState();
    void SetX(double x);
    void SetY(double y);
    void SetState(bool state);
    void Rotate(double phi);       /// Поворот против часовой стрелки вокруг начала координат
    void Translate(double dx, double dy);  /// Сдвиг точки
};

#endif // POINT_H