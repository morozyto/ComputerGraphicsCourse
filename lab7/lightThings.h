//
// Created by Tony Morozov on 20.05.2018.
//
#include "definitions.h"
GLfloat light_position[]={0, 0.2, 1, 1.0};

#ifdef LIGHT_IS_ON

void lightInit() {


    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[]={50.0};
    GLfloat white_light[]={1.0, 1.0, .0, 1.0};
    GLfloat black_light[]= {0.0, 0.0, 0.0, 1.0};
    GLfloat ambient[]= {0.2, 0.2, 0.2, 1.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glEnable(GL_RESCALE_NORMAL);

    //glEnable(GL_NORMALIZE); // glEnable(GL_RESCALE_NORMAL);


}

#endif
