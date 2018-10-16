#ifndef STARSHIP_H
#define STARSHIP_H

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>


#include "texturemanager.h"
#include "coordpoint.h"
#include "bullet.h"

using namespace std;





class Starship
{
public:
    CoordPoint *points;
    vector<GLuint> list_index;
    vector<Bullet> bullets;
    GLint sprites;

    GLuint *pointer_list_index;
    int n_vertex;

    Starship() {
        n_vertex = 4;
        sprites = TextureManager::Inst()->LoadTexture("clipart3.png", GL_BGRA_EXT, GL_RGBA);
        this->create_list_vertex();
        this->create_list_index();
    }

    void create_list_vertex(){
        double x = 0;
        double y = 0.99;

        this->points = new CoordPoint[n_vertex];
        this->points[0].x = -3;
        this->points[0].y = -5;
        this->points[0].z = 0;
        this->points[0].s = 0;
        this->points[0].t = y;


        this->points[1].x = -3;
        this->points[1].y = 0;
        this->points[1].z = 0;
        this->points[1].s = x;
        this->points[1].t = 2.0f;

        this->points[2].x = 1;
        this->points[2].y = 0;
        this->points[2].z = 0;
        this->points[2].s = x+1.0f;
        this->points[2].t = 2.0f;

        this->points[3].x = 1;
        this->points[3].y = -5;
        this->points[3].z = 0;
        this->points[3].s = x+1.0f;
        this->points[3].t = y;
    }

    void create_list_index(){
        list_index = {0,1,2,3};
        this->pointer_list_index = &(this->list_index[0]);
    }

    void set_move(GLfloat x=0, GLfloat y=0){
        for(int i=0; i<n_vertex; i++){
            this->points[i].x += x;
            this->points[i].y += y;
        }
    }

    void shoot_bullet(){
        Bullet bullet(
            (this->points[1].x+this->points[2].x)/2.0f,
            this->points[1].y, 0.3f
        );
        this->bullets.push_back(bullet);
    }

    void draw_bullets(){
        for(int i=0;i<bullets.size();i++){
            bullets[i].first_y += 0.3f;
            bullets[i].display();
        }

    }

    void display(){
        glBindTexture(GL_TEXTURE_2D, sprites);
        glInterleavedArrays(GL_T2F_V3F, sizeof(CoordPoint), &this->points[0].s);
        glDrawElements(GL_QUADS, this->list_index.size() , GL_UNSIGNED_INT, (void*)this->pointer_list_index);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_BLEND);
    }
};

#endif // STARSHIP_H
