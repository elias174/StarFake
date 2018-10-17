#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <iostream>
#include <vector>

#include "asteroids.h"
#include "collision.h"

#include <GL/glut.h>
#include "starship.h"
#include "texturemanager.h"
#include "utils.h"

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define N_ASTEROIDS 10
#define KEY_ESC 27
#define KEY_SPACEBAR 32

using namespace std;


int limit_x = 24;
int limit_y = 10;


Starship *starship  = NULL;
vector<Asteroid> asteroids;
GLint sprites;
GLint texture;
int time_dev = 0;
int timebase = 0;
int anim = 0;
int i = 0;
double x = 0.1678;
double y = 0.665;

void glPaint(void) {

    //El fondo de la escena al color initial
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
    glEnable(GL_BLEND);//utilizar transparencia
    time_dev = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    int dt = time_dev -timebase;// delta time
    timebase = time_dev;
    anim += dt;//duracion de la animacion entre dos cambios de Sprite

    if (anim / 1000.0 > 0.15)// si el tiempo de animacion dura mas 0.15s cambiamos de sprite
    {
        i++;
        anim = 0.0;
    }

    if (i == 6) i = 0;
    int index_asteroid=0;
    for(Asteroid &asteroid : asteroids){
        if(asteroid.destroyed){
            asteroids.erase(asteroids.begin()+index_asteroid);
            continue;
        }
        asteroid.first_y -= 0.01f;
        asteroid.display();
        index_asteroid++;
    }
    starship->display();
    starship->draw_bullets();
    collision_asteroid_bullet(asteroids, starship->bullets);
    glutSwapBuffers();

}

//
//inicializacion de OpenGL
//
void init_GL(void) {
    //Color del fondo de la escena
    glClearColor(0.4f, 0.4f, 0.4f, 0.2f); //(R, G, B, transparencia) en este caso un fondo negro
    glEnable(GL_TEXTURE_2D);
    //modo projeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Get a handle for our "myTextureSampler" uniform
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 50.0f, width / 50.0f, -height / 50.0f, height / 50.0f, -1.0f, 1.0f);

    // todas la informaciones previas se aplican al la matrice del ModelView
    glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
    case KEY_ESC:
        exit(0);
        break;
    case KEY_SPACEBAR:
        starship->shoot_bullet();
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

GLvoid window_idle()
{
    glutPostRedisplay();
}

GLvoid callback_special(int key, int x, int y)
{
    int move_d = 1;
    switch (key)
    {
    case GLUT_KEY_UP:
        starship->set_move(0,move_d);
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        starship->set_move(0,-move_d);
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        starship->set_move(-move_d);
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        starship->set_move(move_d);
        glutPostRedisplay();
        break;
    }
}
int main(int argc, char** argv) {
    //Inicializacion de la GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH_SCREEN, HEIGHT_SCREEN); //tamaño de la ventana
    glutInitWindowPosition(100, 100); //posicion de la ventana
    glutCreateWindow("Textura: Animacion"); //titulo de la ventana

    init_GL(); //fucnion de inicializacion de OpenGL
    for(int i=0; i<N_ASTEROIDS; i++){
        int limit_w = get_random_number(-limit_x, limit_x);
        float limit_h = limit_y;
        Asteroid a_t(limit_w, limit_h);
        asteroids.push_back(a_t);
    }
    starship = new Starship();

    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    // Callback del teclado
    glutKeyboardFunc(&window_key);
    glutSpecialFunc(&callback_special);

    glutIdleFunc(&window_idle);
    glutMainLoop(); //bucle de rendering

    return 0;
}
