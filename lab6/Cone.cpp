//
// Created by Tony Morozov on 17.05.2018.
//

#include "Cone.h"

/// Считает векторное произведение векторов ab и bc

MyVector countNormal(Vertex a, Vertex b, Vertex c) {
    double x1 = a.getX(), x2 = b.getX(), x3 = c.getX();
    double y1 = a.getY(), y2 = b.getY(), y3 = c.getY();
    double z1 = a.getZ(), z2 = b.getZ(), z3 = c.getZ();

    double X1 = x2 - x1, X2 = x3 - x2;
    double Y1 = y2 - y1, Y2 = y3 - y2;
    double Z1 = z2 - z1, Z2 = z3 - z2;

    double x = Y2 * Z1 - Z2 * Y1;
    double y = - X2 * Z1 + X1 * Z2;
    double z = X2 * Y1 - X1 * Y2;

    return {x, y, z};
};

Cone::Cone(double height): top(MyVector(height, 0, height), MyVector(height / 2.0, 0, height),
                                MyVector(height / 4.0, 0, height), MyVector(0, 0, height)), MaxHeight(height) {};


/// Вычисляет опорные точки для кривой Безье для каждой точки в зависимости от разбиение (анимация),
/// вычисляет текущее положение точек в зависимости от t, считает нормали в получившихся точках

void Cone::count_points(int count_of_vertexes_in_circle, int count_of_heights, double t) {

    double precision_ellipse = 2 * M_PI / count_of_vertexes_in_circle;
    double precision_height = MaxHeight / count_of_heights;

    levels.clear();
    double height = 0;
    while (height < MaxHeight) {
        levels.emplace_back(height, precision_ellipse, MaxHeight);
        height += precision_height;
    }

    circles.clear();
    double radius = MaxHeight - precision_height;
    while (radius > 0) {
        circles.emplace_back(radius, precision_ellipse);
        radius -= precision_height;
    }

    count_animation(t);

    /// Вычисление нормалей в точках

    int size = levels.size();
    for (int i = 1; i < size; i++) {
        Level &level_to_down = levels[i - 1], &level_to_up = levels[i];
        vector<Vertex> &points1 = level_to_down.getPoints();
        vector<Vertex> &points2 = level_to_up.getPoints();


        int size2 = points2.size();

        for (int k = 0; k < size2; k++){  //для треугольников с нижним основанием
            MyVector c = countNormal(points1[k], points2[k], points1[(k + 1) % size2]);
            c.normalize();
            points1[k].addNormal(c);
            points2[k].addNormal(c);
            points1[(k + 1) % size2].addNormal(c);
        }

        for (int k = 0; k < size2; k++){  //для треугольников с верхним основанием
            MyVector c = countNormal(points2[k], points2[(k + 1) % size2], points1[(k + 1) % size2]);
            c.normalize();
            points2[k].addNormal(c);
            points2[(k + 1) % size2].addNormal(c);
            points1[(k + 1) % size2].addNormal(c);
        }
    }

    vector<Vertex>& topLevel = levels[size - 1].getPoints();

    int size2 = topLevel.size();

    for (int k = 0; k < size2; k++) {
        MyVector c = countNormal(topLevel[k], top, topLevel[(k + 1) % size2]);
        c.normalize();
        topLevel[k].addNormal(c);
        topLevel[(k + 1) % size2].addNormal(c);
        top.addNormal(c);
    }

    /// Вычисление среднего значения нормали в точке

    for (auto &level: levels) {
        for (auto &point: level.getPoints()) {
            point.countNormal();
        }
    }

    top.countNormal();
}

/// Вычисляет положение каждой точки в зависимости от t

void Cone::count_animation(double t) {
    top.setCoords(t);

    for (auto &g : levels) {
        for (auto &r : g.getPoints()) {
            r.setCoords(t);
        }
    }

    for (auto &g : circles) {
        for (auto &r : g.getPoints()) {
            r.setCoords(t);
        }
    }
}

void Cone::draw() {
    int size = levels.size();
    glBegin(GL_TRIANGLES);

    /// отрисовка стенок

    for (int i = 1; i < size; i++) {
        Level &level_to_down = levels[i - 1], &level_to_up = levels[i];
        vector<Vertex> &points1 = level_to_down.getPoints();
        vector<Vertex> &points2 = level_to_up.getPoints();


        int size2 = points2.size();
        for (int k = 0; k < size2; k++) { // с нижним основанием

            points1[k].draw(i, k);
            points1[(k + 1) % size2].draw(i, k + 1);
            points2[k].draw(i + 1, k);

        }
        for (int k = 0; k < size2; k++) { // с верхним основанием

            points2[k].draw(i + 1, k);
            points1[(k + 1) % size2].draw(i, k + 1);
            points2[(k + 1) % size2].draw(i + 1, k + 1);

        }
    }

    vector<Vertex> &last_level_points = levels[size - 1].getPoints();
    int size2 = last_level_points.size();
    for (int k = 0; k < size2; k++) {

        last_level_points[k].draw(size - 1, k);
        last_level_points[(k + 1) % size2].draw(size - 1, k + 1);
        top.draw(size, k);

    }

    /// отрисовка дна

    size = circles.size();
    glNormal3d(0, 0, -1);
    for (int i = 0; i < size; i++) {
        vector<Vertex> *t = (i == 0) ? &levels[0].getPoints() : &circles[i - 1].getPoints();

        vector<Vertex> &points1 = *t;
        vector<Vertex> &points2 = circles[i].getPoints();


        int size2 = points2.size();
        for (int k = 0; k < size2; k++) { // с нижним основанием

            points1[k].drawNoNormal(i, k);
            points1[(k + 1) % size2].drawNoNormal(i, k + 1);
            points2[k].drawNoNormal(i + 1, k);

        }

        for (int k = 0; k < size2; k++) { // с верхним основанием
            points2[k].drawNoNormal(i + 1, k);
            points1[(k + 1) % size2].drawNoNormal(i, k + 1);
            points2[(k + 1) % size2].drawNoNormal(i + 1, k + 1);

        }

    }

    vector<Vertex> *t = size == 0 ? &levels[0].getPoints() : &circles[size - 1].getPoints();
    vector<Vertex>& points = *t;

    Vertex middle;

    size2 = points.size();
    for (int k = 0; k < size2; k++) {
        points[k].drawNoNormal( size, k);
        points[(k + 1) % size2].drawNoNormal( size, k + 1);
        middle.drawNoNormal(size + 1, k);
    }

    glEnd();
}
