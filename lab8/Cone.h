
#include <vector>
#include "Level.h"
#include "Circle.h"
#include <cmath>


#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>

using std::vector;

// Класс для отрисовки моего наклонного эллептического консуса.

class Cone {
public:
    Cone(double MaxHeight);
    ~Cone();
    void count_points(int count_of_vertexes, int count_of_heights);
    void draw();
private:
    vector<Level> levels;
    vector<Circle> circles;
    double MaxHeight;

    int count1, count2;

    GLuint *VBO, *VAO;
};