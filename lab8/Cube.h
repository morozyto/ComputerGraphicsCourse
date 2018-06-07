
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube {
public:
    Cube(double size);
    void draw();
    ~Cube();

private:

    GLuint *VBO, *VAO;

    double size;
    void initDataOfEdge(int index, double* data, int len);
};