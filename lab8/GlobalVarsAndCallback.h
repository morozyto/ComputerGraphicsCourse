#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

#include "Cone.h"
#include "Cube.h"
#include "shaderThings.h"

using std::vector;

//// Необходимые данные для поворотов, сдвигов, масштабирования
float angle1, angle2, angle3;
float x_pos = 0., y_pos = 0., z_pos = 0., scale = 0.5;

/// Необходимо для динамического изменения размера окна
int global_size;

/// Для динамического изменения точности отображения фигуры
int count_of_levels = 6;
int count_of_vertexes_in_circle = 6;

double MaxHeight = 1.0;          // Высота конуса
Cone* cone;            // Объект конуса
Cube* cube;                 // Объект кубика


vector<glm::mat4> *transformMat, *projectMat; // Вектор матриц для отрисовки кубика и конуса в каждом фрейме и
                                                // вектор проекций для каждого фрейма

//Вычисляет матрицы для отрисовки кубика и конуса
void count_mat() {

    for (int i = 0; i < 3; i++) {
        (*transformMat)[2*i] = glm::translate((*projectMat)[i], glm::vec3(-0.7f, -0.7f, -0.7));

        (*transformMat)[2*i + 1] = glm::translate((*projectMat)[i], glm::vec3(x_pos, y_pos, z_pos));
        (*transformMat)[2*i + 1] = glm::rotate((*transformMat)[2*i + 1], angle1, glm::vec3(1.f, 0.f, 0.f));
        (*transformMat)[2*i + 1] = glm::rotate((*transformMat)[2*i + 1], angle2, glm::vec3(0.f, 1.f, 0.f));
        (*transformMat)[2*i + 1] = glm::rotate((*transformMat)[2*i + 1], angle3, glm::vec3(0.f, 0.f, 1.0f));
        (*transformMat)[2*i + 1] = glm::scale((*transformMat)[2*i + 1], glm::vec3(scale, scale, scale));
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    static bool SkeletonMode = false;

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
        cone->count_points(count_of_vertexes_in_circle, count_of_levels);
    }
    if (key == GLFW_KEY_N && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_vertexes_in_circle != 1) {
            count_of_vertexes_in_circle -= 1;
            cone->count_points(count_of_vertexes_in_circle, count_of_levels);

        }
    }
    if (key == GLFW_KEY_J && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        count_of_levels += 1;
        cone->count_points(count_of_vertexes_in_circle, count_of_levels);
    }
    if (key == GLFW_KEY_K && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_levels != 1) {
            count_of_levels -= 1;
            cone->count_points(count_of_vertexes_in_circle, count_of_levels);
        }
    }
    if (key == GLFW_KEY_DOWN && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 += 0.02;
    }
    if (key == GLFW_KEY_UP && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 -= 0.02;
    }
    if (key == GLFW_KEY_Q && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 -= 0.02;
    }
    if (key == GLFW_KEY_E && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 += 0.02;
    }
    if (key == GLFW_KEY_LEFT && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 -= 0.02;
    }
    if (key == GLFW_KEY_RIGHT && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 += 0.02;
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
        scale += 0.01;
    }
    if (key ==GLFW_KEY_X && (action  == GLFW_REPEAT || action == GLFW_PRESS)) {
        scale -= 0.01;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    count_mat();
}

void WindowCallbackSize(GLFWwindow* window, int width, int height) {
    glfwGetFramebufferSize(window, &width, &height);
    if (height >= width) {
        global_size = width;
    } else {
        global_size = height;
    }
}