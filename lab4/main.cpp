#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
//#include <iostream>
#include <vector>
#include "MyBuffer.h"
#include "Filter.h"

using namespace std;

int window_width, window_height;  // Размеры буфера
int x, y;  // Координаты курсора во время клика

bool EndOfPoints = false;  // Флаг окончания ввода точек
bool Filter = false;  // Флаг постфильтрации

MyBuffer* buffer;  // Здесь хранятся данные, которые занесутся в буфер цвета
GLfloat* AccBuffer;  // Аккмулирующий буфер (Аппаратной поддержки нет)

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static int my_round(double k) {
    if (k >= 0) {
        return int(k + 0.5);
    } else {
        return int(k - 0.5);
    }
}

/*
 * Из-за особенностей Retina дисплея, ноутбук выделяет бОльший объем памяти(в 2*2 раза), чем размеры окна, которое
 * я создаю. Проблема в том, что координаты клика идут в координатах размера окна, когда как пиксель соответсвует совсем
 * другой координате. Ну и еще мне удобнее работать, когда координата y растёт снизу вверх.
 */
void getCoords(GLFWwindow* window) {


    double a, b;
    glfwGetCursorPos(window, &a, &b);

    a *= 2;
    b = window_height - b*2;

    x = my_round(a);
    y = my_round(b);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {  // затравить пикселем, где находится курсор
        getCoords(window);

        buffer->coloring(x, y);
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {  // применить пост-фильтрацию
        Filter = !Filter;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {  // окончание ввода точек
        if (!EndOfPoints) {
            getCoords(window);

            vector<int> b;
            b.push_back(x);
            b.push_back(y);
            buffer->addPoint(b);

            EndOfPoints = true;

            buffer->draw_line_with_previous();
            buffer->draw_last_line();
        }
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {  // очистка ввода
        Filter = false;
        EndOfPoints = false;
        buffer->Refresh();
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mode) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (!EndOfPoints) {
            getCoords(window);

            vector<int> b;
            b.push_back(x);
            b.push_back(y);
            buffer->addPoint(b);
            buffer->draw_line_with_previous();
        }
    }
}

static void WindowCallbackSize(GLFWwindow* window, int width, int height) {
    glfwGetFramebufferSize(window, &width, &height);
    window_height = height;
    window_width = width;
    buffer->Resize(height, width);
    delete[] AccBuffer;
    AccBuffer = new GLfloat[window_width*window_height*3];

    Filter = false;
    EndOfPoints = false;

    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(800, 800, "Laba4", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, WindowCallbackSize);
    glfwSetMouseButtonCallback(window, mouse_callback);

    glfwGetFramebufferSize(window, &window_width, &window_height);
    buffer = new MyBuffer(window_height, window_width);
    AccBuffer = new GLfloat[window_width*window_height*3];

    glViewport(0, 0, window_width, window_height);
    glRasterPos2i(-1, -1);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 0);

        glClear(GL_COLOR_BUFFER_BIT);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, buffer->GetPixels());

        if (Filter) {
            PostFilter(buffer, window_width, window_height, AccBuffer);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    delete buffer;
    delete[] AccBuffer;
    glfwTerminate();
    exit(EXIT_SUCCESS);
}