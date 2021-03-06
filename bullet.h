#ifndef BULLET_H
#define BULLET_H

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "coordpoint.h"
#include "texturemanager.h"
#include "utils.h"

using namespace std;

class Bullet
{
public:
    int n_vertex;
    GLfloat heigth, width;
    GLfloat first_x, first_y;
    GLfloat trail_length;
    GLint sprites;


    Bullet(GLfloat first_x, GLfloat first_y, GLfloat width) {
        sprites = TextureManager::Inst()->LoadTexture("sprite_bullet.png", GL_BGRA_EXT, GL_RGBA);
        this->first_x = first_x;
        this->first_y = first_y;
        n_vertex = 4;
        heigth = 0.9f;
        this->width = 0.2f;
        trail_length = 0.4f;
    }

    void display(){
        GLfloat x = 0.15f;
        GLfloat y = 0.55f;
        glPushMatrix();
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, sprites);
            glBegin(GL_QUADS);
                glTexCoord2f(x, 0.1f);//coordenadas de textura
                glVertex3f(first_x , first_y, 0.0f);   // Top
                glTexCoord2f(x, y+0.6f);//coordenadas de textura
                glVertex3f(first_x , first_y + heigth, 0.0f);   // Top
                glTexCoord2f(x+0.6f, y+0.6f);//coordenadas de textura
                glVertex3f(first_x + width , first_y + heigth, 0.0f);   // Top
                glTexCoord2f(x+0.6f, 0.1f);//coordenadas de textura
                glVertex3f(first_x+width, first_y, 0.0f);   // Top
            glEnd();
            //glDisable(GL_BLEND);
        glPopMatrix();
    }

    coords get_center_collide(){
        GLfloat center_collide_x = (first_x + (first_x+width))/2.0f;
        GLfloat center_collide_y = (first_y + (first_y+heigth))/2.0f;
        coords my_center = make_pair(center_collide_x, center_collide_y + (heigth/4.0f));
        return  my_center;
    }

    GLfloat get_radio_collide(){
        coords first_vertex = make_pair(first_x, first_y+heigth);
        return distance_points(get_center_collide(), first_vertex);
    }

};


#endif // BULLET_H
