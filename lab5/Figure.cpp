#include "Figure.h"

Figure::Figure() {}

void Figure::addPoint(double x, double y, bool state) {
    pointsOfFigure.emplace_back(x, y, state);
}

void Figure::addPoint(double x, double y) {
    addPoint(x, y, true);
}

void Figure::addPoint(Point &t) {
    pointsOfFigure.push_back(t);
}
int Figure::size() {
    return pointsOfFigure.size();
}
Point&  Figure::getPoint(int number_of_point) {
    return pointsOfFigure[number_of_point % pointsOfFigure.size()];
}

void Figure::setPoint(int number_of_point, double new_x, double new_y, bool state) {
    Point point = getPoint(number_of_point);
    point.SetX(new_x);
    point.SetY(new_y);
    point.SetState(state);
}

void Figure::rotateAllPoints(double phi) {
    for (auto &point: pointsOfFigure) {
        point.Rotate(phi);
    }
}

void Figure::translateAllPoints(double dx, double dy) {
    for (auto &point: pointsOfFigure) {
        point.Translate(dx, dy);
    }
}

bool Figure::check_clockwise() {
    int n = pointsOfFigure.size();
    double sum = 0;

    for (int i = 0; i < n - 1; i++) {
        sum += pointsOfFigure[i].GetX() * pointsOfFigure[i+1].GetY();
    }
    sum += pointsOfFigure[n - 1].GetX() * pointsOfFigure[0].GetY();

    for (int i = 0; i < n - 1; i++) {
        sum -= pointsOfFigure[i + 1].GetX() * pointsOfFigure[i].GetY();
    }

    sum -= pointsOfFigure[0].GetX() * pointsOfFigure[n - 1].GetY();

    return sum >= 0;
}

void Figure::do_clockwise() {
    if (!check_clockwise()) {
        vector<Point> newPoints;

        for (int i = pointsOfFigure.size() - 1; i >= 0; i--) {
            newPoints.push_back(pointsOfFigure[i]);
        }

        pointsOfFigure = newPoints;
    }
}

bool Figure::check_vertex(int i) {
    auto some = *this;
    if (size() <= 3) return true;
    dx = -getPoint(i).GetX();
    dy = -getPoint(i).GetY();
    some.translateAllPoints(dx, dy);

    phi = atan2(some.getPoint(i + 1).GetY(), some.getPoint(i + 1).GetX());

    some.rotateAllPoints(-phi);

    return (some.getPoint(i + 2).GetY() >= -0.0000002);
}

vector<Figure> Figure::do_convex_figures() {
    vector<Figure> res;

    Figure current, another;

    for (int i = 0; i < pointsOfFigure.size(); i++) {
        if (!check_vertex(i)) {
            current.addPoint(getPoint(i + 1).GetX(), getPoint(i + 1).GetY(), false);

            another.addPoint(getPoint(i + 1));

            auto some = *this;

            some.translateAllPoints(dx, dy);
            some.rotateAllPoints(-phi);

            int k = i + 2;

            some.setPoint(i + 1, getPoint(i + 1).GetX(), 0, getPoint(i + 1).GetState());

            while ((!check_intersection(some.getPoint(k - 1), some.getPoint(k), Point(0, 0), Point(4, 0))
                   || (check_intersection(some.getPoint(k - 1), some.getPoint(k), Point(0, 0), Point(4, 0))
                       && intersection(some.getPoint(k - 1), some.getPoint(k), Point(-1, 0), Point(1, 0)).GetX() < 0)
                                                                                            || (k - 2) == i) && k < 2*size() ) {
                another.addPoint(getPoint(k));
                k++;
            }

            Point t = intersection(some.getPoint(k - 1), some.getPoint(k), Point(-1, 0), Point(1, 0));

            if (!some.getPoint(k - 1).GetState()) t.SetState(false);
            t.SetY(0);
            t.Rotate(phi);
            t.Translate(-dx, -dy);

            another.addPoint(t.GetX(), t.GetY(), false);
            current.addPoint(t);


            while (k % pointsOfFigure.size() != (i + 1) % pointsOfFigure.size()) {
                current.addPoint(getPoint(k));
                k++;
            }

            res.push_back(current);
            res.push_back(another);
            return res;
        }
    }


    res.push_back(*this);
    return res;
}

void Figure::drawFigure() {
    for (auto &point : pointsOfFigure) {
        glVertex2d(point.GetX(), point.GetY());
    }
}

void Figure::drawFigureWithHoles() {
    if (!pointsOfFigure.empty()) {
        glBegin(GL_LINE_STRIP);
        for (auto &point : pointsOfFigure) {
            glVertex2d(point.GetX(), point.GetY());
            if (!point.GetState()) {
                glEnd();
                glBegin(GL_LINE_STRIP);
            }
        }
        glVertex2d(pointsOfFigure[0].GetX(), pointsOfFigure[0].GetY());
        glEnd();
    }
}

void Figure::refresh() {
    pointsOfFigure.clear();
}

int Figure::sign(double n) {
    if (n > 0) return 1;
    if (n == 0) return 0;
    return -1;
}

Figure Figure::Sutherland_Hodgman(Figure convexFigure, Figure &cutter) {

    cutter.addPoint(cutter.getPoint(0));
    Figure tempResult;
    Point firstPoint, previousPoint;

    for (int i = 0; i < cutter.size() - 1; i++) {
        tempResult.refresh();
        for (int j = 0; j < convexFigure.size(); j++) {

            if (j != 0) {

                if (check_intersection(previousPoint, convexFigure.getPoint(j), cutter.getPoint(i), cutter.getPoint(i + 1))) {
                    auto Tintersec = intersection(previousPoint, convexFigure.getPoint(j), cutter.getPoint(i), cutter.getPoint(i + 1));

                    auto SVisib = Visibility(convexFigure.getPoint(j), cutter.getPoint(i), cutter.getPoint(i + 1));

                    if (!convexFigure.getPoint(j - 1).GetState() && SVisib >= 0) {
                        Tintersec.SetState(false);
                    }

                    tempResult.addPoint(Tintersec);
                }

            } else {
                firstPoint = convexFigure.getPoint(j);
            }
            previousPoint = convexFigure.getPoint(j);
            auto SVisib = Visibility(previousPoint, cutter.getPoint(i), cutter.getPoint(i + 1));
            if (SVisib >= 0) {
                tempResult.addPoint(previousPoint);
            }
        }
        if (tempResult.size() != 0) {
            if (check_intersection(previousPoint, firstPoint, cutter.getPoint(i), cutter.getPoint(i + 1))) {
                auto Tintersec = intersection(previousPoint, firstPoint, cutter.getPoint(i), cutter.getPoint(i + 1));

                auto SVisib = Visibility(firstPoint, cutter.getPoint(i), cutter.getPoint(i + 1));

                if (!previousPoint.GetState() && SVisib >= 0) {
                    Tintersec.SetState(false);
                }

                tempResult.addPoint(Tintersec);
            }
        }  else {
            return tempResult;
        }

        convexFigure = tempResult;
    }
    return tempResult;
}


int Figure::Visibility(Point &point, Point &P1, Point &P2) {
    auto Rab1 = (point.GetX() - P1.GetX()) * (P2.GetY() - P1.GetY());
    auto Rab2 = (point.GetY() - P1.GetY()) * (P2.GetX() - P1.GetX());
    auto Rab3 = Rab2 - Rab1;
    return sign(Rab3);
}

bool Figure::check_intersection(Point &begin, Point &end, Point W1, Point W2) {
    auto Visib1 = Visibility(begin, W1, W2);
    auto Visib2 = Visibility(end, W1, W2);

    return (Visib1 * Visib2 < 0);
}

Point Figure::intersection(Point P1, Point P2, Point W1, Point W2) {
    double coef[2][2];
    coef[0][0] = P2.GetX() - P1.GetX();
    coef[0][1] = W1.GetX() - W2.GetX();
    coef[1][0] = P2.GetY() - P1.GetY();
    coef[1][1] = W1.GetY() - W2.GetY();

    double right[2];
    right[0] = W1.GetX() - P1.GetX();
    right[1] = W1.GetY() - P1.GetY();

    auto det = coef[0][0] * coef[1][1] - coef[1][0] * coef[0][1];

    double a, b, c, d;
    a = coef[1][1] / det;
    d = coef[0][0] / det;
    b = -coef[0][1] / det;
    c = -coef[1][0] / det;

    coef[0][0] = a;
    coef[0][1] = b;
    coef[1][0] = c;
    coef[1][1] = d;

    auto param1 = coef[0][0] * right[0] + coef[0][1] * right[1];

    auto x = P1.GetX() + (P2.GetX() - P1.GetX()) * param1;
    auto y = P1.GetY() + (P2.GetY() - P1.GetY()) * param1;

    return {x, y};
}

vector<Point> Figure::getPoints() {
    return pointsOfFigure;
}

void Figure::addEdge(Point t1, Point t2) {
    vector<Point> e;
    e.push_back(t1);
    e.push_back(t2);
    edges.push_back(e);
}

void Figure::draw_with_edges() {
    for (auto &edge: edges) {
        glVertex2d(edge[0].GetX(), edge[0].GetY());
        glVertex2d(edge[1].GetX(), edge[1].GetY());
    }
}

int findEdgeWithPoint(vector<vector<Point>> edges, Point point) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i][0].GetX() == point.GetX() && edges[i][0].GetY() == point.GetY()) {
            return i;
        }
    }
}

bool check_using(vector<int> a, int t) {
    for (auto &g : a) {
        if (g == t) return true;
    }
    return false;
}
//bool checkUsed(int index, )

vector<Figure> Figure::doFigures() {
    vector<Figure> res;
    vector<int> used;
   // used.push_back(0);
    vector<Point> current_edge;// = edges[0];

    for (int i = 0; i < edges.size(); i++) {
        if (!check_using(used, i)) {
            used.push_back(i);
            current_edge = edges[i];

            Figure current;

            current.addPoint(current_edge[0]);

            int k = findEdgeWithPoint(edges, current_edge[1]);
          //  cout << "check 1" << endl;
            while (k != i) {
                current.addPoint(edges[k][0]);
                k = findEdgeWithPoint(edges, edges[k][1]);
           //     cout << "k = " << k << endl;
            }
          //  cout << "check 2" << endl;
            res.push_back(current);
        }
    }
    return res;
}