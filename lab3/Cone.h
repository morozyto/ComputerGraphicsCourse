#include <vector>
#include "Level.h"
#include "Circle.h"
#include <GLFW/glfw3.h>

using namespace std::vector;

class Cone {
public:
    Cone(double MaxHeight);
    void count_points(int count_of_vertexes, int count_of_heights);
    void draw();
private:
    vector<Level> levels;
    vector<Circle> circles;
    double MaxHeight;
};