#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
//#include <math.h>
#include <GL/glut.h>

using namespace std;

typedef pair<GLfloat, GLfloat> coords;


GLfloat distance_points(coords first, coords second){
    GLfloat first_component = pow(second.first-first.first, 2.0f);
    GLfloat second_component = pow(second.second-first.second, 2.0f);
    return sqrt(first_component+second_component);
}

int get_random_number(int a, int b){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a,b);
    return dist6(rng);
}


#endif // UTILS_H
