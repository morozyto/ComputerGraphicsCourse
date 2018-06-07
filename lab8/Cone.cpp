#include "Cone.h"

Cone::Cone(double height){
    this->MaxHeight = height;

    VBO = new GLuint[2];
    VAO = new GLuint[2];

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

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

    vector<double> data;

    int size = levels.size();
    for (int i = 0; i < size - 1; i++) {
        Level &level_to_down = levels[i], &level_to_up = levels[i + 1];
        vector<vector<double>> &points1 = level_to_down.getPoints();
        vector<vector<double>> &points2 = level_to_up.getPoints();
        double colour_var;

        int size2 = points2.size();
        for (int k = 0; k < size2; k++){
            colour_var = pow((float)k / size2 - 0.5, 2.) + 0.25f;  //Для плавного изменения цвета

            data.push_back(points1[k][0]);
            data.push_back(points1[k][1]);
            data.push_back(points1[k][2]);
            data.push_back(colour_var * 2);
            data.push_back((float)i / size);
            data.push_back(2*colour_var + (float)i / size);

            data.push_back(points2[k][0]);
            data.push_back(points2[k][1]);
            data.push_back(points2[k][2]);
            data.push_back(colour_var * 2);
            data.push_back((float)i / size);
            data.push_back(2*colour_var + (float)i / size);
        }

        data.push_back(points1[0][0]);
        data.push_back(points1[0][1]);
        data.push_back(points1[0][2]);
        data.push_back(colour_var * 2);
        data.push_back((float)i / size);
        data.push_back(2*colour_var + (float)i / size);

        data.push_back(points2[0][0]);
        data.push_back(points2[0][1]);
        data.push_back(points2[0][2]);
        data.push_back(colour_var * 2);
        data.push_back((float)i / size);
        data.push_back(2*colour_var + (float)i / size);
    }

    count1 = data.size() / 6;

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(double), &data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)(3* sizeof(GLdouble)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    data.clear();

    size = levels.size();
    for (int i = 0; i < size - 1; i++) {
        Circle &circle_bigger = circles[i], &circle_smaller = circles[i + 1];
        vector<vector<double>> &points1 = circle_bigger.getPoints();
        vector<vector<double>> &points2 = circle_smaller.getPoints();

        double colour_var;

        int size2 = points2.size();
        for (int k = 0; k < size2; k++){
            colour_var = pow((float)k / size2 - 0.5, 2.) + 0.25f;

            data.push_back(points1[k][0]);
            data.push_back(points1[k][1]);
            data.push_back(points1[k][2]);
            data.push_back(colour_var * 2);
            data.push_back((float)i / size);
            data.push_back(2*colour_var + (float)i / size);

            data.push_back(points2[k][0]);
            data.push_back(points2[k][1]);
            data.push_back(points2[k][2]);
            data.push_back(colour_var * 2);
            data.push_back((float)i / size);
            data.push_back(2*colour_var + (float)i / size);
        }
        data.push_back(points1[0][0]);
        data.push_back(points1[0][1]);
        data.push_back(points1[0][2]);
        data.push_back(colour_var * 2);
        data.push_back((float)i / size);
        data.push_back(2*colour_var + (float)i / size);

        data.push_back(points2[0][0]);
        data.push_back(points2[0][1]);
        data.push_back(points2[0][2]);
        data.push_back(colour_var * 2);
        data.push_back((float)i / size);
        data.push_back(2*colour_var + (float)i / size);
    }

    count2 = data.size() / 6;
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(double), &data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid*)(3* sizeof(GLdouble)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Cone::draw() {
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, count1);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, count2);
    glBindVertexArray(0);
}

Cone::~Cone() {
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    delete[] VBO;
    delete[] VAO;
}