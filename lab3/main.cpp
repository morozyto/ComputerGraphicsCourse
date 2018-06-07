#include <GLFW/glfw3.h>
#include "Cone.h"
#include "Cube.h"
#include "projections.h"

using namespace std;

//// Необходимые данные для поворотов, сдвигов, масштабирования
int angle1, angle2, angle3;
double x_pos = 0., y_pos = 0., z_pos = 0., scale = 1.;

/// Необходимо для динамического изменения размера окна
int global_size;

/// Для динамического изменения точности отображения фигуры
int count_of_levels = 6;
int count_of_vertexes_in_circle = 6;

double MaxHeight = 1.0;          // Высота конуса
Cone cone(MaxHeight);            // Объект конуса
Cube cube(0.05);                 // Объект кубика


/// Отрисовывает кубик
void draw_little_cube();

/// Отрисовывает четвертинку экрана; projection - одна из функций из projections.h
void draw_frame(void (*projection)());

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

bool SkeletonMode = false;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if (SkeletonMode) {
            SkeletonMode = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            SkeletonMode = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    if (key == GLFW_KEY_M && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        count_of_vertexes_in_circle += 1;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels);
    }
    if (key == GLFW_KEY_N && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_vertexes_in_circle != 1) {
            count_of_vertexes_in_circle -= 1;
            cone.count_points(count_of_vertexes_in_circle, count_of_levels);
        }
    }
    if (key == GLFW_KEY_J && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        count_of_levels += 1;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels);
    }
    if (key == GLFW_KEY_K && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_levels != 1) {
            count_of_levels -= 1;
            cone.count_points(count_of_vertexes_in_circle, count_of_levels);
        }
    }
    if (key == GLFW_KEY_DOWN && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 += 1;
    }
    if (key == GLFW_KEY_UP && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 -= 1;
    }
    if (key == GLFW_KEY_Q && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 -= 1;
    }
    if (key == GLFW_KEY_E && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 += 1;
    }
    if (key == GLFW_KEY_LEFT && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 -= 1;
    }
    if (key == GLFW_KEY_RIGHT && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 += 1;
    }
    if (key == GLFW_KEY_D && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        x_pos += 0.01;
    }
    if (key == GLFW_KEY_A && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        x_pos -= 0.01;
    }
    if (key == GLFW_KEY_R && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        y_pos += 0.01;
    }
    if (key == GLFW_KEY_T && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        y_pos -= 0.01;
    }
    if (key == GLFW_KEY_S && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        z_pos -= 0.01;
    }
    if (key == GLFW_KEY_W && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        z_pos += 0.01;
    }
    if (key == GLFW_KEY_Z && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        scale += 0.1;
    }
    if (key ==GLFW_KEY_X && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        scale -= 0.1;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void WindowCallbackSize(GLFWwindow* window, int width, int height) {
    glfwGetFramebufferSize(window, &width, &height);
    if (height >= width) {
        global_size = width;
    } else {
        global_size = height;
    }
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(1000, 1000, "Laba3", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, WindowCallbackSize);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height >= width) {
        global_size = width;
    } else {
        global_size = height;
    }

    glEnable(GL_DEPTH_TEST);
    cone.count_points(count_of_vertexes_in_circle, count_of_levels);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, global_size / 2, global_size / 2);
        draw_frame(make_orth_front);

        glViewport(0, global_size/2, global_size/2, global_size/2);
        draw_frame(make_orth_top);

        glViewport(global_size/2, global_size/2, global_size/2, global_size/2);
        draw_frame(make_orth_side);

        glViewport(global_size/2, 0, global_size/2, global_size/2);
        draw_frame(make_perspective);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void draw_frame(void (*projection)() ) {

    glMatrixMode(GL_PROJECTION_MATRIX);
    (*projection)();

    glMatrixMode(GL_MODELVIEW_MATRIX);

    draw_little_cube();

    glPushMatrix();
    glTranslated(x_pos, y_pos, z_pos);
    glRotated(angle1, 1., 0., 0.);
    glRotated(angle2, 0., 1., 0.);
    glRotated(angle3, 0., 0., 1.);
    glScalef(scale, scale, 2 * scale);

    cone.draw();

    glPopMatrix();
}

void draw_little_cube(){
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix();
    glTranslated(-0.5, -0.5, -0.5);
    cube.draw();
    glPopMatrix();
}