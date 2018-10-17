#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "coordpoint.h"
#include "texturemanager.h"
#include "utils.h"

using namespace std;


class Asteroid
{
public:
    int n_vertex;
    GLfloat heigth, width;
    GLfloat first_x, first_y;
    GLfloat trail_length;
    GLint sprites;
    bool destroyed;

    Asteroid(GLfloat first_x, GLfloat first_y) {
        sprites = TextureManager::Inst()->LoadTexture("animated_asteroid.png", GL_BGRA_EXT, GL_RGBA);
        this->first_x = first_x;
        this->first_y = first_y;
        n_vertex = 4;
        heigth = 3.0f;
        this->width = 2.2f;
        destroyed = false;
    }

    void display(){
        GLfloat x = 0.0f;
        GLfloat y = 0.45f;

        GLfloat increment_x = 0.056f;
        glPushMatrix();
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, sprites);
            glBegin(GL_QUADS);
                glTexCoord2f(x, 0.0f);//coordenadas de textura
                glVertex3f(first_x , first_y, 0.0f);   // Top
                glTexCoord2f(x, y);//coordenadas de textura
                glVertex3f(first_x , first_y + heigth, 0.0f);   // Top
                glTexCoord2f(x+increment_x, y);//coordenadas de textura
                glVertex3f(first_x + width , first_y + heigth, 0.0f);   // Top
                glTexCoord2f(x+increment_x, 0.0f);//coordenadas de textura
                glVertex3f(first_x+width, first_y, 0.0f);   // Top
            glEnd();
            //glDisable(GL_BLEND);
        glPopMatrix();
    }

    coords get_center_collide(){
        GLfloat center_collide_x = (first_x + (first_x+width))/2.0f;
        GLfloat center_collide_y = (first_y + (first_y+heigth))/2.0f;
        coords my_center = make_pair(center_collide_x, center_collide_y);
        return  my_center;
    }

    GLfloat get_radio_collide(){
        GLfloat my_radio = heigth/2.0f;
        return my_radio;
    }

    bool detect_collision(coords center, GLfloat radio){
        return radio+get_radio_collide() > distance_points(get_center_collide(), center);
    }

};

#endif // ASTEROIDS_H
