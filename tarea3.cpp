#define GL_SILENCE_DEPRECATION
#include <cmath>
#include <stdlib.h>
#include "GLUT/glut.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "glut32.lib")
#define WINDOW_TITLE "Project"
using namespace std;

void init(void) {
    glClearColor(.5, .5, .5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void teclado(unsigned char Key, int x, int y) {
    switch (Key)
    {
    case 'x':
        exit(1);
    default:
        break;
    }
}

void color_pick(int color) {
    switch (color)
    {
    case 0:
        glColor3f(0.925, 0, 0);//Red
        break;
    case 1:
        glColor3f(0, 0.25, 0.4);//Dark Blue
        break;
    case 2:
        glColor3f(0, 0.65, 0.925);//Light Blue
        break;
    case 3:
        glColor3f(0.88,0.725,0.58);
    default:
        break;
    }
}

void square(double x, double y, double size, int color) {
    color_pick(color);
    glBegin(GL_POLYGON_BIT);
    glVertex3f(x, y, 0);
    glVertex3f(x + size, y, 0);
    glVertex3f(x, y - size, 0);
    glVertex3f(x+size, y - size, 0);
    glEnd();
}


void circle(double x, double y, double r){
    x+=r;
    y-=r;
    r*=0.75;
    glBegin(GL_POLYGON);
    for(double theta=0; theta<=2*M_PI; theta+=0.01){
        glVertex3f(x+r*cos(theta),y+r*sin(theta),0);
    }
    glEnd();
}
void elipse(double x, double y, double rx, double ry, double theta_ini){
    glBegin(GL_POLYGON);
    for(double theta=0+theta_ini;theta<=M_PI+theta_ini; theta+=0.01){
        glVertex3f(x+rx*cos(theta),y+ry*sin(theta),0);
    }
    glEnd();
}


void circle_type(double x, double y, double r, int color, int type){
    color_pick(color);
    switch(type){
        case 0:
            circle(x,y,r);
            break;
        case 1:
            elipse(x+r,y, r, r*(-0.3), 0);
            elipse(x+r,y-r*2, r, r*0.3, 0);
            break;
        case 2:
            elipse(x,y-r, r*(-0.3),r, M_PI/2);
            elipse(x+r*2,y-r, r*0.3 ,r, M_PI/2);
            break;
        default:
            break;
    }
}

void display(){
    double size=0.1;
    int color_square,color_circle, type_circle;
    for(double x = -0.8; x <= 0.8; x += size){
        for(double y = -0.8; y <= 0.8; y += size){
            color_square=rand() % 4;
            do{
                color_circle=rand() % 4;
            } while(color_square==color_circle);
            type_circle=rand() % 3;
            square(x,y,size,color_square);
            circle_type(x,y,size/2, color_circle, type_circle);
        }
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(50, 100); //Posiciona la ventana
    glutInitWindowSize(800, 800);//Tamaño en pixel
    glutCreateWindow("Collateral Damage - Peter McClure"); //Titulo de la ventana
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
