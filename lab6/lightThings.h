//
// Created by Tony Morozov on 20.05.2018.
//

#ifndef LAB6_LIGHTTHINGS_H
#define LAB6_LIGHTTHINGS_H

GLfloat light_position[]={0, 0, 1, 1.0};

void lightInit() {
    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[]={50.0};
    GLfloat white_light[]={1.0, 1.0, .0, 1.0};
    GLfloat black_light[]= {0.0, 0.0, 0.0, 1.0};
    GLfloat ambient[]= {0.2, 0.2, 0.2, 1.0};

    //   GLfloat direction[] = {1.0, 1.0, 1.0};


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE); // glEnable(GL_RESCALE_NORMAL);
}

#endif //LAB6_LIGHTTHINGS_H
