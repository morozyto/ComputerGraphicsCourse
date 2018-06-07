#include "GlobalVarsAndCallback.h"

/// Отрисовывает четвертинку экрана; t1 и t2 - (проекционная матрица * видовую) для кубика и конуса соответственно.
void draw_frame(int i, GLint shader, GLint transformLoc);

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // OSX users

    window = glfwCreateWindow(1000, 1000, "Laba8", NULL, NULL);
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

    GLint shader;

    shadersInit(shader);

    cube = new Cube(0.05);
    cone = new Cone(MaxHeight);

    glEnable(GL_DEPTH_TEST);
    cone->count_points(count_of_vertexes_in_circle, count_of_levels);

    GLint transformLoc = glGetUniformLocation(shader, "transform");

   // glm::mat4 transCube1, transCone1, transCube2, transCone1, transCube3, transCone3;
    projectMat = new vector<glm::mat4>();
    transformMat = new vector<glm::mat4>();

    glm::mat4 matrix(1.0f);

    projectMat->push_back(glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0.f, 0.f, 1.f)));
    projectMat->push_back(glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0.f, 1.f, 0.f)));
    projectMat->push_back(glm::rotate(matrix, glm::radians(90.0f), glm::vec3(1.f, 0.f, 0.f)));

    for (int i = 0; i < 6; i++) transformMat->emplace_back(1.0f);

    count_mat();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glViewport(0, 0, global_size / 2, global_size / 2);
        draw_frame(0, shader, transformLoc);

        glViewport(0, global_size / 2, global_size / 2, global_size / 2);
        draw_frame(1, shader, transformLoc);

        glViewport(global_size / 2, global_size / 2, global_size / 2, global_size / 2);
        draw_frame(2, shader, transformLoc);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    delete cube;
    delete cone;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void draw_frame(int i, GLint shader, GLint transformLoc) {

    glUseProgram(shader);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr((*transformMat)[2*i]));

    cube->draw();

    glUseProgram(shader);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr((*transformMat)[2*i + 1]));

    cone->draw();
}

