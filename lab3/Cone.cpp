#include "Cone.h"

Cone::Cone(double height){
    this->MaxHeight = height;
};

void Cone::count_points(int count_of_vertexes_in_circle, int count_of_heights) {
    double precision_ellipse = 2 * M_PI / count_of_vertexes_in_circle;
    double precision_height = MaxHeight / count_of_heights;

    levels.clear();
    double height = 0;
    while (height < MaxHeight) {
        levels.emplace_back(height, precision_ellipse, MaxHeight);
        height += precision_height;
    }
    levels.emplace_back(MaxHeight, precision_ellipse, MaxHeight);

    circles.clear();
    double radius = MaxHeight;
    while (radius > 0) {
        circles.emplace_back(radius, precision_ellipse);
        radius -= precision_height;
    }
    circles.emplace_back(0, precision_ellipse);
}

void Cone::draw() {
    int size = levels.size();
    for (int i = 0; i < size - 1; i++) {
        Level &level_to_down = levels[i], &level_to_up = levels[i + 1];
        vector<vector<double>> &points1 = level_to_down.getPoints();
        vector<vector<double>> &points2 = level_to_up.getPoints();

        glBegin(GL_TRIANGLE_STRIP);
        int size2 = points2.size();
        for (int k = 0; k < size2; k++){
            double colour_var = pow(((float)k / size2 - 0.5), 2.) + 0.25f;  //Для плавного изменения цвета
            glColor3f(colour_var * 2, (float)i / size , 2*colour_var + (float)i / size);
            glVertex3f(points1[k][0], points1[k][1], points1[k][2]);
            glVertex3f(points2[k][0], points2[k][1], points2[k][2]);
        }
        glVertex3f(points1[0][0], points1[0][1], points1[0][2]);
        glVertex3f(points2[0][0], points2[0][1], points2[0][2]);
        glEnd();
    }

    size = levels.size();
    for (int i = 0; i < size - 1; i++) {
        Circle &circle_bigger = circles[i], &circle_smaller = circles[i + 1];
        vector<vector<double>> &points1 = circle_bigger.getPoints();
        vector<vector<double>> &points2 = circle_smaller.getPoints();

        glBegin(GL_TRIANGLE_STRIP);
        int size2 = points2.size();
        for (int k = 0; k < size2; k++){
            double colour_var = pow(((float)k / size2 - 0.5), 2.) + 0.25f;
            glColor3f(colour_var * 2, (float)i / size , 2*colour_var + (float)i / size);
            glVertex3f(points1[k][0], points1[k][1], points1[k][2]);
            glVertex3f(points2[k][0], points2[k][1], points2[k][2]);
        }
        glVertex3f(points1[0][0], points1[0][1], points1[0][2]);
        glVertex3f(points2[0][0], points2[0][1], points2[0][2]);
        glEnd();
    }
}