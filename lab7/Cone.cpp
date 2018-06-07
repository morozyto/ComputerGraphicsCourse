//
// Created by Tony Morozov on 17.05.2018.
//



#include "Cone.h"

#ifdef DISPLAYLIST_IS_ON
bool isFirstList = true;
#endif


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

#ifdef LIGHT_IS_ON

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
#endif

#ifdef ARRAYLIST_IS_ON
    countArrays();
#endif

#ifdef DISPLAYLIST_IS_ON
    if (isFirstList) isFirstList = false;
    else glDeleteLists(1, 1);

    glNewList(1, GL_COMPILE);
    draw();
    glEndList();

#endif


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

















void Cone::countArrays() {
    points_side.clear();
    normals_side.clear();

    points_top.clear();
    normals_top.clear();

    points_down.clear();
    points_down_mid.clear();

    int size = levels.size();

    for (int i = 1; i < size; i++) {
        Level &level_to_down = levels[i - 1], &level_to_up = levels[i];
        vector<Vertex> &points1 = level_to_down.getPoints();
        vector<Vertex> &points2 = level_to_up.getPoints();

        int size2 = points2.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON


        for (int k = 0; k <= size2; k++) { // с нижним основанием

            points2[k % size2].addCoordsToArray(points_side);
            points1[k % size2].addCoordsToArray(points_side);

            points2[k % size2].addNormalToArray(normals_side);
            points1[k % size2].addNormalToArray(normals_side);

        }

#else


        for (int k = 0; k < size2; k++) { // с нижним основанием

            points1[k].addCoordsToArray(points_side);
            points1[(k + 1) % size2].addCoordsToArray(points_side);
            points2[k].addCoordsToArray(points_side);

            points1[k].addNormalToArray(normals_side);
            points1[(k + 1) % size2].addNormalToArray(normals_side);
            points2[k].addNormalToArray(normals_side);

        }
        for (int k = 0; k < size2; k++) { // с верхним основанием

            points2[k].addCoordsToArray(points_side);
            points1[(k + 1) % size2].addCoordsToArray(points_side);
            points2[(k + 1) % size2].addCoordsToArray(points_side);

            points2[k].addNormalToArray(normals_side);
            points1[(k + 1) % size2].addNormalToArray(normals_side);
            points2[(k + 1) % size2].addNormalToArray(normals_side);

        }

#endif


    }


    vector<Vertex> &last_level_points = levels[size - 1].getPoints();
    int size2 = last_level_points.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    top.addCoordsToArray(points_top);
    top.addNormalToArray(normals_top);

    for (int k = 0; k <= size2; k++) {

        last_level_points[k % size2].addCoordsToArray(points_top);

        last_level_points[k % size2].addNormalToArray(normals_top);

    }


#else


    for (int k = 0; k < size2; k++) {

        last_level_points[k].addCoordsToArray(points_top);
        last_level_points[(k + 1) % size2].addCoordsToArray(points_top);
        top.addCoordsToArray(points_top);

        last_level_points[k].addNormalToArray(normals_top);
        last_level_points[(k + 1) % size2].addNormalToArray(normals_top);
        top.addNormalToArray(normals_top);

    }

#endif


    /// отрисовка дна

    size = circles.size();
    glNormal3d(0, 0, -1);
    for (int i = 0; i < size; i++) {
        vector<Vertex> *t = (i == 0) ? &levels[0].getPoints() : &circles[i - 1].getPoints();

        vector<Vertex> &points1 = *t;
        vector<Vertex> &points2 = circles[i].getPoints();


        int size2 = points2.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

        for (int k = 0; k <= size2; k++) {

            points2[k % size2].addCoordsToArray(points_down);
            points1[k % size2].addCoordsToArray(points_down);

        }

#else


        for (int k = 0; k < size2; k++) { // с нижним основанием

            points1[k].addCoordsToArray(points_down);
            points1[(k + 1) % size2].addCoordsToArray(points_down);
            points2[k].addCoordsToArray(points_down);

        }

        for (int k = 0; k < size2; k++) { // с верхним основанием

            points2[k].addCoordsToArray(points_down);
            points1[(k + 1) % size2].addCoordsToArray(points_down);
            points2[(k + 1) % size2].addCoordsToArray(points_down);

        }

#endif

    }

    vector<Vertex> *t = size == 0 ? &levels[0].getPoints() : &circles[size - 1].getPoints();
    vector<Vertex>& points = *t;

    Vertex middle;

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    middle.addCoordsToArray(points_down_mid);

    for (int k = 0; k <= size2; k++) {

     points[k % size2].addCoordsToArray(points_down_mid);
    }

#else

    for (int k = 0; k < size2; k++) {

        points[k].addCoordsToArray(points_down_mid);
        points[(k + 1) % size2].addCoordsToArray(points_down_mid);
        middle.addCoordsToArray(points_down_mid);
    }

#endif


}




void Cone::draw() {



#ifdef ARRAYLIST_IS_ON

    glEnableClientState(GL_VERTEX_ARRAY);

#ifdef LIGHT_IS_ON
    glEnableClientState(GL_NORMAL_ARRAY);
#endif

    glVertexPointer(3, GL_DOUBLE, 0, &points_side[0]);

    #ifdef LIGHT_IS_ON
    glNormalPointer(GL_DOUBLE, 0, &normals_side[0]);
    #endif


#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    glDrawArrays(GL_TRIANGLE_STRIP, 0, points_side.size() / 3);

#else

    glDrawArrays(GL_TRIANGLES, 0, points_side.size() / 3);

#endif


    glVertexPointer(3, GL_DOUBLE, 0, &points_top[0]);

    #ifdef LIGHT_IS_ON
    glNormalPointer(GL_DOUBLE, 0, &normals_top[0]);
    #endif

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    glDrawArrays(GL_TRIANGLE_FAN, 0, points_top.size() / 3);

#else

    glDrawArrays(GL_TRIANGLES, 0, points_top.size() / 3);

#endif

    glDisableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_DOUBLE, 0, &points_down[0]);
    glNormal3d(0, 0, -1);


#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    glDrawArrays(GL_TRIANGLE_STRIP, 0, points_down.size() / 3);

#else

    glDrawArrays(GL_TRIANGLES, 0, points_down.size() / 3);

#endif

    glVertexPointer(3, GL_DOUBLE, 0, &points_down_mid[0]);

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    glDrawArrays(GL_TRIANGLE_FAN, 0, points_down_mid.size() / 3);

#else

    glDrawArrays(GL_TRIANGLES, 0, points_down_mid.size() / 3);

#endif
    glDisableClientState(GL_VERTEX_ARRAY);



#else

    int size = levels.size();



#ifndef TRIANGLE_FAN_AND_STRIP_IS_ON
    glBegin(GL_TRIANGLES);
#endif
    /// отрисовка стенок

    for (int i = 1; i < size; i++) {
        Level &level_to_down = levels[i - 1], &level_to_up = levels[i];
        vector<Vertex> &points1 = level_to_down.getPoints();
        vector<Vertex> &points2 = level_to_up.getPoints();

        int size2 = points2.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON


        glBegin(GL_TRIANGLE_STRIP);
        for (int k = 0; k <= size2; k++) { // с нижним основанием

            points2[k % size2].draw(i + 1, k);
            points1[k % size2].draw(i, k);

        }
        glEnd();

#else


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

#endif
    }

#ifndef TRIANGLE_FAN_AND_STRIP_IS_ON
    glEnd();
#endif

    vector<Vertex> &last_level_points = levels[size - 1].getPoints();
    int size2 = last_level_points.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    #ifdef TEXTURE_IS_ON


    glBegin(GL_TRIANGLES);

    for (int k = 0; k < size2; k++) {

        last_level_points[k].draw(size - 1, k);
        last_level_points[(k + 1) % size2].draw(size - 1, k + 1);
        top.draw(size, k);

    }

    #else


    glBegin(GL_TRIANGLE_FAN);
    top.draw(size, 0);

    for (int k = 0; k <= size2; k++) {

        last_level_points[k % size2].draw(size - 1, k);

    }

    #endif
    glEnd();

#else

    glBegin(GL_TRIANGLES);

    for (int k = 0; k < size2; k++) {

        last_level_points[k].draw(size - 1, k);
        last_level_points[(k + 1) % size2].draw(size - 1, k + 1);
        top.draw(size, k);

    }
    glEnd();


#endif

    /// отрисовка дна

#ifndef TRIANGLE_FAN_AND_STRIP_IS_ON
    glBegin(GL_TRIANGLES);
#endif

    size = circles.size();
    glNormal3d(0, 0, -1);
    for (int i = 0; i < size; i++) {
        vector<Vertex> *t = (i == 0) ? &levels[0].getPoints() : &circles[i - 1].getPoints();

        vector<Vertex> &points1 = *t;
        vector<Vertex> &points2 = circles[i].getPoints();


        int size2 = points2.size();

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

        glBegin(GL_TRIANGLE_STRIP);
        for (int k = 0; k <= size2; k++) {

            points2[k % size2].drawNoNormal(i + 1, k);
            points1[k % size2].drawNoNormal(i, k);

        }
        glEnd();

#else


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

#endif

    }

#ifndef TRIANGLE_FAN_AND_STRIP_IS_ON
    glEnd();
#endif



    vector<Vertex> *t = size == 0 ? &levels[0].getPoints() : &circles[size - 1].getPoints();
    vector<Vertex>& points = *t;

    Vertex middle;

#ifdef TRIANGLE_FAN_AND_STRIP_IS_ON

    #ifdef TEXTURE_IS_ON


    glBegin(GL_TRIANGLES);
    for (int k = 0; k < size2; k++) {
        points[k].drawNoNormal( size, k);
        points[(k + 1) % size2].drawNoNormal( size, k + 1);
        middle.drawNoNormal(size + 1, k);
    }

    glEnd();

    #else


    glBegin(GL_TRIANGLE_FAN);
    middle.drawNoNormal(size + 1, 0);

    for (int k = 0; k <= size2; k++) {
        points[k % size2].drawNoNormal( size, k);
    }
    glEnd();


    #endif

#else

    glBegin(GL_TRIANGLES);
    for (int k = 0; k < size2; k++) {
        points[k].drawNoNormal( size, k);
        points[(k + 1) % size2].drawNoNormal( size, k + 1);
        middle.drawNoNormal(size + 1, k);
    }

    glEnd();

#endif

#endif

}

