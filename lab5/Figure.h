#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Point.h"
#include <iostream>

using namespace std;

class Figure {
private:

    vector<Point> pointsOfFigure;

    bool check_clockwise();  /// Проверить, введены ли вершины по часовой стрелке

    bool check_vertex(int i); /// Проверить, является ли вершина (i + 1) выпуклой

    double phi = 0, dx = 0, dy = 0; /// Для нахождения разбиения на выпуклые, приходится двигать и крутить фигуру

    vector<vector<Point> > edges;

public:
    Figure();

    void addEdge(Point t1, Point t2);
    void draw_with_edges();
    void addPoint(double x, double y);

    void addPoint(double x, double y, bool state);

    void addPoint(Point &t);

    int size();

    Point& getPoint(int number_of_point);

    vector<Point> getPoints();

    void setPoint(int number_of_point, double new_x, double new_y, bool new_state);

    void rotateAllPoints(double phi);

    void translateAllPoints(double dx, double dy);

    void do_clockwise();   /// Перебирать точки против часовой стрелки

    vector<Figure> do_convex_figures();  /// Сделать из невыпуклой фигуры множество выпуклых

    void drawFigure();  /// Нарисовать фигуру без учета "невидимых" граней

    void drawFigureWithHoles();  /// Нарисовать фигуру с учетом "невидимых" граней

    void refresh();

    int sign(double n);

    Figure Sutherland_Hodgman(Figure convexFigure, Figure &cutter);  /// Отсечь выпуклую фигуру выпуклым отсекателем

    int Visibility(Point &point, Point &P1, Point &P2); /// Проверка видимости точки относительно ребра P1-P2

    bool check_intersection(Point &begin, Point &end, Point W1, Point W2);  /// Проверить, пересекается ли отрезок begin-end c W1-W2

    Point intersection(Point P1, Point P2, Point W1, Point W2);  /// Найти точку пересечения

    vector<Figure> doFigures();

    //int findEdgeWithPoint(vector<vector<Point>> edges, Point point);
};

#endif //FIGURE_H