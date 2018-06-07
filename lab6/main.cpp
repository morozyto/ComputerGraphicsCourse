#include "globalVarsAndCallbacks.h"

/// Отрисовывает кубик
void draw_little_cube();

/// Отрисовывает четвертинку экрана; projection - одна из функций из projections.h
void draw_frame(void (*projection)());

int main(void)
{
    GLFWInit();
    lightInit();
    textureInit();

    cone.count_points(count_of_vertexes_in_circle, count_of_levels, t);

    while (!glfwWindowShouldClose(window))
    {
        countt();

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



    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    draw_little_cube();

    glPushMatrix();
    glTranslated(x_pos, y_pos, z_pos);
    glRotated(angle1, 1., 0., 0.);
    glRotated(angle2, 0., 1., 0.);
    glRotated(angle3, 0., 0., 1.);
    glScalef(scale, scale, scale);
    cone.draw();

    glPopMatrix();
}

void draw_little_cube(){
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix();
    glTranslated(light_position[0], light_position[1], light_position[2]);
    cube.draw();
    glPopMatrix();
}
