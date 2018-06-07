#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Figure.h"

using std::vector;

int window_width, window_height;  /// Размеры буфера
double x, y;                        /// Координаты курсора во время клика

Figure* figure;             /// Отсекаемая фигура
Figure* cutter_figure;      /// Отсекатель
vector<Figure> convex_figures; /// Разбиение исходной фигуры на выпуклые
vector<Figure> result_figures;  /// Вектор фигур, являющихся результатом
Figure* result;

vector<Figure> RESULT_FIGURES;

bool isCutterPoints = false; /// Флаг ввода точек отсекателя
bool isEndOfPoints = false;  /// Флаг окончания ввода точек
bool isConvexing = false;    /// Флаг для "отображения" разбиения

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static void Refresh() {
    isEndOfPoints = false;
    isCutterPoints = false;
    isConvexing = false;

    figure->refresh();
    cutter_figure->refresh();
    convex_figures.clear();
    result_figures.clear();
    RESULT_FIGURES.clear();
    delete result;
    result = NULL;
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

    x = a * 2 / window_width - 1.0;
    y = b * 2 / window_height - 1.0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {  /// Выполнить отсечение
        if (isEndOfPoints) {
            for (auto const &convex_figure : convex_figures) {
                Figure t = figure->Sutherland_Hodgman(convex_figure, *cutter_figure);
                result_figures.push_back(t);
            }

            delete result;
            result = new Figure();

         //   cout << "hmm" << endl;

            for (auto &figure1 : result_figures) {
                auto a = figure1.getPoints();
                int size = figure1.size();
               // cout << "size = " << size << endl;

                for (int i = 0; i < size; i++) {
                //    cout << i << " " << a[i].GetState() << endl;
                    if (a[i].GetState()) {
                        result->addEdge(a[i], a[(i + 1) % size]);
                    }
                }
            }
           // cout << "ha" << endl;
            RESULT_FIGURES = result->doFigures();
           // cout << "heh" << endl;
        }

    }

    if (key == GLFW_KEY_T && action == GLFW_PRESS) {  /// Нарисовать разбиение на выпуклые
        isConvexing = !isConvexing;
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {  /// первое нажатие - окончание ввода фигуры
                                                      /// второе нажатие - окончание ввода отсекателя
        if (!isEndOfPoints) {

            getCoords(window);

            if (!isCutterPoints) {
                figure->addPoint(x, y);
                figure->do_clockwise();

                vector<Figure> stack, some_figures;
                stack.push_back(*figure);
                while (!stack.empty()) {
                    auto t = stack[stack.size() - 1];

                    stack.pop_back();
                    some_figures = t.do_convex_figures();
                    if (some_figures.size() == 2) {
                           stack.push_back(some_figures[0]);
                           stack.push_back(some_figures[1]);
                    } else {
                           convex_figures.push_back(some_figures[0]);
                    }
                }
                isCutterPoints = true;

            } else {
                cutter_figure->addPoint(x, y);
                cutter_figure->do_clockwise();
                isEndOfPoints = true;
            }

        }
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {  // очистка ввода
        Refresh();
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mode) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (!isEndOfPoints) {
            getCoords(window);

            if (!isCutterPoints) figure->addPoint(x, y);
            else cutter_figure->addPoint(x, y);
        }
    }
}

static void WindowCallbackSize(GLFWwindow* window, int width, int height) {

    glfwGetFramebufferSize(window, &width, &height);
    window_height = height;
    window_width = width;

    if (window_height >= window_width) glViewport(0, 0, window_width, window_width);
    else glViewport(0, 0, window_height, window_height);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(800, 800, "Laba5", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, WindowCallbackSize);
    glfwSetMouseButtonCallback(window, mouse_callback);

    glfwGetFramebufferSize(window, &window_width, &window_height);

    if (window_height >= window_width) glViewport(0, 0, window_width, window_width);
    else glViewport(0, 0, window_height, window_height);

    figure = new Figure();
    cutter_figure = new Figure();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 0.f, 0.f);
        glBegin(GL_LINE_LOOP);

        figure->drawFigure();
        if (!isCutterPoints) {
            getCoords(window);
            glVertex2d(x, y);
        }
        glEnd();

        glColor3f(0.f, 1.f, 0.f);
        glBegin(GL_LINE_LOOP);

        cutter_figure->drawFigure();
        if (!isEndOfPoints) {
            getCoords(window);
            glVertex2d(x, y);
        }
        glEnd();

        if (isConvexing) {
            glColor3d(1., 1., 1.);
            for (auto &figure : convex_figures) {
                glBegin(GL_LINE_LOOP);

                figure.drawFigure();

                glEnd();
            }
        }

        glColor3f(0.f, 0.f, 1.f);

        for (auto &figure1 : RESULT_FIGURES) {
            glBegin(GL_LINE_LOOP);

            figure1.drawFigure();

            glEnd();
        }

      //  if (result != NULL) {
      //  glBegin(GL_LINES);
       // if (result != NULL) result->draw_with_edges();
      //  glEnd();
       // }
       /* for (auto &figure : result_figures) {
            figure.drawFigureWithHoles();
        }
*/
        glfwWaitEvents();
        glfwSwapBuffers(window);
    }

    delete figure;
    delete cutter_figure;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


/*if (key == GLFW_KEY_E && action == GLFW_PRESS) {  // окончание ввода точек
        if (!isEndOfPoints) {

            getCoords(window);

            if (!isCutterPoints) {
                figure->addPoint(x, y);
                figure->do_clockwise();

               // check_points_figure(*figure);
                vector<Figure> stack, some_figures;
                stack.push_back(*figure);
                while (!stack.empty()) {
                    auto t = stack[stack.size() - 1];
                  //  cout << stack.size() << endl;
                   // check_points_figure(t);
                    if (stack.size() > 100) {
                  //      cout << "WOW" << endl;
                        break;
                    }
                    stack.pop_back();
                    some_figures = t.do_convex_figures();
                    if (some_figures.size() == 2) {
                           stack.push_back(some_figures[0]);
                           stack.push_back(some_figures[1]);
                    } else {
                           convex_figures.push_back(some_figures[0]);
                    }
                }

                //convex_figures.push_back(*figure); /////////
                isCutterPoints = true;
            } else {
                cutter_figure->addPoint(x, y);
                cutter_figure->do_clockwise();
                isEndOfPoints = true;
            }

        }
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {

        figure->addPoint(-0.741133, 0.775373);   //0
        figure->addPoint(-0.616318, -0.0205746); //1
        figure->addPoint(-0.886123, -0.500645);  //2
        figure->addPoint(-0.608604, -0.94122);  //3
        figure->addPoint(-0.365039, -0.382218); //4
        figure->addPoint(-0.12042, -0.850161); //5
        figure->addPoint(0.21166, -0.475433); //6
        figure->addPoint(0.388486, -0.877006); //7
        figure->addPoint(0.799941, -0.934869);//8
        figure->addPoint(0.876543, -0.345827); //9
        figure->addPoint(0.353467, -0.320141);//10
        figure->addPoint(-0.128018, -0.503911); //11
        figure->addPoint(-0.346289, -0.124768); //12
        figure->addPoint(-0.583135, -0.412369); //13
        figure->addPoint(-0.43459, 0.0769456); //14
        figure->addPoint(0.0823242, -0.304667); //15
        figure->addPoint(0.841104, -0.0625403); //16
        figure->addPoint(0.804961, 0.32877); //17
        figure->addPoint(0.247959, 0.00454637); //18
        figure->addPoint(-0.376318, 0.280494); //19
        figure->addPoint(0.761963, 0.525907); //20
        figure->addPoint(0.781455, 0.813246); //21
        figure->addPoint(0.0160449, 0.574284); //22
        figure->addPoint(-0.474893, 0.834073); //23

        figure->do_clockwise();

        vector<Figure> stack, some_figures;
        stack.push_back(*figure);
        bool flag = true;
        isConvexing = true;

        while (!stack.empty()) {

            auto t = stack[stack.size() - 1];
            stack.pop_back();
            cout << "check t " << endl;
            check_points_figure(t);
            some_figures = t.do_convex_figures();
            cout << "check working convexing" << endl;
            if (some_figures.size() == 2) {
                stack.push_back(some_figures[0]);
                stack.push_back(some_figures[1]);
                cout << "ADDED: " << endl;
                check_points_figure(some_figures[0]);
                check_points_figure(some_figures[1]);

               // cout << "BEGINNING" << endl;
              //  check_points_figure(*figure);
              //  cout << "ENDING";

                if (flag) {
                  //  convex_figures.push_back(some_figures[0]); //////////УБРАТЬ ПОТОМ ОБЯЗАТЕЛЬНО

                    flag = false;

                }


            } else {
                convex_figures.push_back(some_figures[0]);
                cout << "POPPED: " << endl;
                check_points_figure(some_figures[0]);
            }
        }
        isEndOfPoints = true;
        isCutterPoints = true;

        for (auto const &convex_figure : convex_figures) {
          //  check_points_figure(convex_figure);
          //  cout << "dividi" << endl;
        }

        cutter_figure->addPoint(-0.5, -0.5);
        cutter_figure->addPoint(0.5, -0.5);
        cutter_figure->addPoint(0.5, 0.5);
        cutter_figure->addPoint(-0.5, 0.5);

        cutter_figure->do_clockwise();

        /*
        auto h = stack[stack.size() - 1];
        check_points_figure(h);
        h = stack[0];
        cout << "DIVIDING" << endl;
        check_points_figure(h);


        cout << "START EXPIREMENT" << endl;
        some_figures = stack[0].do_convex_figures();
        if (some_figures.size() == 1) {
            cout << "RIGHT" << endl;
            check_points_figure(some_figures[0]);
        } else {
            cout << "NOT RIGHT" << endl;
            check_points_figure(some_figures[0]);
            cout << "divide mini " << endl;
            check_points_figure(some_figures[1]);
        }
         *
      //  }

    }
*/
/*
bool check_points_figure(Figure g) {
    for (auto &t: g.getPoints()) {
        cout << "figure->addPoint(" << t.GetX() << ", " << t.GetY() << " " << t.GetState() << ");" << endl;
    }
    cout << "end" << endl;
}
*/