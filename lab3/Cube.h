#include <GLFW/glfw3.h>

class Cube {
public:
    Cube(double size);
    void draw();
private:
    double size;
    void draw_edge(double *edge, double* colour);
};