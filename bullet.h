#ifndef BULLET_H
#define BULLET_H

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "coordpoint.h"
#include "texturemanager.h"

using namespace std;

class Bullet
{
public:
    int n_vertex;
    GLfloat heigth, width;
    GLfloat first_x, first_y;
    GLfloat trail_length;

    Bullet(GLfloat first_x, GLfloat first_y, GLfloat width) {
        this->first_x = first_x;
        this->first_y = first_y;
        n_vertex = 4;
        heigth = 0.5f;
        this->width = width;
        trail_length = 0.4f;
    }

    void display(){
        glPushMatrix();
            glBegin(GL_QUADS);
                glVertex3f(first_x , first_y, 0.0f);   // Top
                glVertex3f(first_x , first_y + heigth, 0.0f);   // Top
                glVertex3f(first_x + width , first_y + heigth, 0.0f);   // Top
                glVertex3f(first_x+width, first_y, 0.0f);   // Top
            glEnd();
        glPopMatrix();
    }

};


#endif // BULLET_H
