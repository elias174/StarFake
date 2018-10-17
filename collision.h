#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <vector>

#include "asteroids.h"
#include "bullet.h"
#include "utils.h"
#include "starship.h"

using namespace std;

void collision_asteroid_bullet(vector<Asteroid> &asteroids, vector<Bullet> &bullets, Starship *starship, bool &game_over){
    int index_bullet = 0;
    for(Asteroid &asteroid : asteroids){
        bool collided = false;
        for(Bullet &bullet: bullets){
            coords bullet_center = bullet.get_center_collide();
            GLfloat bullet_radio = bullet.get_radio_collide();
            if(asteroid.detect_collision(bullet_center, bullet_radio)){
                bullets.erase(bullets.begin()+index_bullet);
                asteroid.destroyed = true;
                collided = true;
                break;
            }
            index_bullet++;
        }
        coords center_starship = starship->get_center_collide();
        GLfloat radio_starship = starship->get_radio();
        if(asteroid.detect_collision(center_starship, radio_starship)){
            cout << "collidsaa" << endl;
            game_over = true;
        }
    }
}

#endif // COLLISION_H
