//
// Created by Tony Morozov on 20.05.2018.
//

#ifndef LAB6_GLOBALVARSANDCALLBACKS_H
#define LAB6_GLOBALVARSANDCALLBACKS_H

#include <fstream>
#include "Cone.h"
#include "Cube.h"
#include "projections.h"
#include "textureThings.h"
#include "lightThings.h"

/// Необходимые данные для поворотов, сдвигов, масштабирования
int angle1, angle2, angle3;
double x_pos = 0., y_pos = 0., z_pos = 0., scale = 1.;

/// Состояние сцены: каркасный режим или нет, с тексторой или без
bool SkeletonMode = false;
bool TextureMode = false;
bool isMoving = false;
bool isUp = true;

/// Параметр в отрезке [0, 1], определяющий состояние анимации
double t = 0.0;

/// Необходимо для динамического изменения размера окна
int global_size;

/// Для динамического изменения точности отображения фигуры
int count_of_levels = 12;
int count_of_vertexes_in_circle = 24;

double MaxHeight = 1.0;          // Высота конуса
Cone cone(MaxHeight);            // Объект конуса
Cube cube(0.05);                 // Объект кубика

/// Параметры для ослабления света с расстоянием
double CONSTANT_ATTENUATION = 1.0;
double LINEAR_ATTENUATION = 0.0;
double QUADRATIC_ATTENUATION = 0.0;

/// Объект окна пользователя
GLFWwindow* window;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void countt() {
    if (isMoving) {
        if (isUp) {
            t = min(1.0, t + 0.02);
            if (t == 1.0) isUp = false;
        } else {
            t = max(.0, t - 0.02);
            if (t == 0.0) isUp = true;
        }
        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);

    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if (SkeletonMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        SkeletonMode = !SkeletonMode;
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        if (TextureMode) {
            glShadeModel(GL_SMOOTH);
            glDisable(GL_TEXTURE_2D);
        } else {
            glShadeModel(GL_FLAT);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glBindTexture(GL_TEXTURE_2D, texName);
        }
        TextureMode = !TextureMode;
    }
    if (key == GLFW_KEY_1 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        CONSTANT_ATTENUATION += 0.01;
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, CONSTANT_ATTENUATION);
    }
    if (key == GLFW_KEY_2 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        CONSTANT_ATTENUATION = max(0., CONSTANT_ATTENUATION - 0.01);
        if (CONSTANT_ATTENUATION == 0 && LINEAR_ATTENUATION == 0 && QUADRATIC_ATTENUATION == 0) CONSTANT_ATTENUATION = 0.01;
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, CONSTANT_ATTENUATION);
    }
    if (key == GLFW_KEY_3 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        LINEAR_ATTENUATION += 0.01;
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, LINEAR_ATTENUATION);
    }
    if (key == GLFW_KEY_4 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        LINEAR_ATTENUATION = max(0., LINEAR_ATTENUATION - 0.01);
        if (LINEAR_ATTENUATION == 0 && CONSTANT_ATTENUATION == 0 && QUADRATIC_ATTENUATION == 0) LINEAR_ATTENUATION = 0.01;
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, LINEAR_ATTENUATION);
    }
    if (key == GLFW_KEY_5 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        QUADRATIC_ATTENUATION += 0.01;
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, QUADRATIC_ATTENUATION);
    }
    if (key == GLFW_KEY_6 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        QUADRATIC_ATTENUATION = max(0., QUADRATIC_ATTENUATION - 0.01);
        if (CONSTANT_ATTENUATION == 0 && LINEAR_ATTENUATION == 0 && QUADRATIC_ATTENUATION == 0) QUADRATIC_ATTENUATION = 0.01;
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, QUADRATIC_ATTENUATION);
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        isMoving = !isMoving;
    }
       /* t = min(1.0, t + 0.02);
        if (t == 1.0) cout << "t = 1 !" << endl;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
    }

    if (key == GLFW_KEY_8 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        t = max(0.0, t - 0.02);
        if (t == 0.0) cout << "t = 0 !" << endl;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
    }
        */
    if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        ofstream fout("../STORAGEDATA.txt");
        if (!fout.is_open()) {
            cout << "Problems with file!" << endl;
            return;
        }

        fout << angle1 <<  " " << angle2 << " " << angle3 << " " << scale << endl;
        fout << x_pos << " " << y_pos << " " << z_pos << endl;
        fout << SkeletonMode << " " << TextureMode << " " << t << " " << global_size << " " << count_of_levels << endl;
        fout << count_of_vertexes_in_circle << " " << CONSTANT_ATTENUATION << " " << LINEAR_ATTENUATION << " " <<
             QUADRATIC_ATTENUATION << endl;

        fout.close();
    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        ifstream fin("../STORAGEDATA.txt");
        if (!fin.is_open()) {
            cout << "Problems with file!" << endl;
            return;
        }

        fin >> angle1 >> angle2 >> angle3 >> scale >> x_pos >> y_pos >> z_pos >> SkeletonMode >> TextureMode;
        fin >> t >> global_size >> count_of_levels >> count_of_vertexes_in_circle >> CONSTANT_ATTENUATION;
        fin >> LINEAR_ATTENUATION >> QUADRATIC_ATTENUATION;

        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
        fin.close();
    }
    if (key == GLFW_KEY_M && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        count_of_vertexes_in_circle += 1;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
    }
    if (key == GLFW_KEY_N && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_vertexes_in_circle != 1) {
            count_of_vertexes_in_circle -= 1;
            cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
        }
    }
    if (key == GLFW_KEY_J && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        count_of_levels += 1;
        cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
    }
    if (key == GLFW_KEY_K && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (count_of_levels != 1) {
            count_of_levels -= 1;
            cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);
        }
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 += 1;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle1 -= 1;
    }
    if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 -= 1;
    }
    if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle2 += 1;
    }
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 -= 1;
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        angle3 += 1;
    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        x_pos += 0.1;
    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        x_pos -= 0.1;
    }
    if (key == GLFW_KEY_R && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        y_pos += 0.1;
    }
    if (key == GLFW_KEY_T && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        y_pos -= 0.1;
    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        z_pos -= 0.1;
    }
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        z_pos += 0.1;
    }
    if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        scale += 0.1;
    }
    if (key ==GLFW_KEY_X && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
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

void GLFWInit() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(1000, 1000, "Laba6", NULL, NULL);
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
}

#endif //LAB6_GLOBALVARSANDCALLBACKS_H
