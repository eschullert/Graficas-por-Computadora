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

double ng = M_PI / 2; //Noventa grados
//Basado en cuentas de que dentro de cada cuadrado deberia de haber un
double radio = 75 / sqrt(2); //Radio de los segmentos de circulos
double theta = 1.2309594173407746821; //Mitad del angulo que se forma entre el centro y las dos esquinas del segmento
double matrix[16];
double esquina00[4] = { 0.0, 0.0, 1.0, 1.0 };
double esquina01[4] = { 700.0, 0.0, 1.0, 1.0 };
double esquina10[4] = { 0.0, 500.0, 1.0, 1.0 };
double esquina11[4] = { 700.0, 500.0, 1.0, 1.0 };
double x, y;

void init(void) {
    glClearColor(.5, .5, .5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION); //
    //gluOrtho2D(-100.0, 800.0, -100.0, 600.0); //Coordenadas de visualización
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
    //for(double theta=theta_start; theta<=theta_end; theta+=0.01){
    //    glVertex3f(x+r*cos(theta),y+r*sin(theta),0);
    //}
}

/*
void segmentoCirculo(double thetaIni, double thetaFin, double cx, double cy) {
    //Esta funcion deberia de incluir el radio en la llamada, pero siempre es el mismo
    for (double a = thetaIni; a <= thetaFin; a += (M_PI / 200)) {
        glVertex3f(cx + radio * cos(a), cy + radio * sin(a), 0);
    }
}

void circulo(double x, double y, int r) {
    glBegin(GL_POLYGON);
    switch (r)
    {
    case 1: //Viendo abajo
        glVertex3f(x, y - 50, 0);
        segmentoCirculo(ng - theta, ng + theta, x - 50, y - 50 - (radio / 3));
        glVertex3f(x - 100, y - 50, 0);
        break;
    case 2: //Viendo arriba
        glVertex3f(x - 100, y, 0);
        segmentoCirculo(3 * ng - theta, 3 * ng + theta, x - 50, y + (radio / 3));
        glVertex3f(x, y, 0);
        break;
    case 3://viendo izquierda
        glVertex3f(x - 50, y - 100, 0);
        segmentoCirculo(4 * ng - theta, 4 * ng + theta, x - 50 - (radio / 3), y - 50);
        glVertex3f(x - 50, y, 0);
        break;
    case 4: //viendo derecha
        glVertex3f(x, y, 0);
        segmentoCirculo(2 * ng - theta, 2 * ng + theta, x + (radio / 3), y - 50);
        glVertex3f(x, y - 100, 0);
        break;
    default:
        break;
    }
    glEnd();
}

void miniCuadro(double x, double y, int colorCua, int colorCir, int rotacion1, int rotacion2) {
    eligeColor(colorCua);
    cuadrado(x, y);

    eligeColor(colorCir);
    if (rotacion1 <= 2) {
        circulo(x, y, rotacion1);
        circulo(x, y - 50, rotacion2);
    }
    else {
        circulo(x - 50, y, rotacion1);
        circulo(x, y, rotacion2);
    }
}

void cuadro(void) {
    glClear(GL_COLOR_BUFFER_BIT); //
    //1
    miniCuadro(100, 500, 1, 2, 4, 4);
    miniCuadro(200, 500, 3, 1, 3, 4);
    miniCuadro(300, 500, 1, 2, 1, 1);
    miniCuadro(400, 500, 1, 3, 1, 1);
    miniCuadro(500, 500, 2, 3, 1, 2);
    miniCuadro(600, 500, 3, 1, 4, 3);
    miniCuadro(700, 500, 3, 1, 4, 4);

    //2
    miniCuadro(100, 400, 2, 1, 4, 4);
    miniCuadro(200, 400, 3, 2, 1, 1);
    miniCuadro(300, 400, 2, 1, 3, 3);
    miniCuadro(400, 400, 1, 3, 2, 1);
    miniCuadro(500, 400, 1, 3, 3, 3);
    miniCuadro(600, 400, 3, 1, 2, 1);
    miniCuadro(700, 400, 2, 3, 3, 3);

    //3
    miniCuadro(100, 300, 3, 1, 3, 3);
    miniCuadro(200, 300, 3, 2, 4, 4);
    miniCuadro(300, 300, 1, 3, 2, 1);
    miniCuadro(400, 300, 2, 1, 3, 3);
    miniCuadro(500, 300, 2, 3, 4, 4);
    miniCuadro(600, 300, 1, 2, 3, 4);
    miniCuadro(700, 300, 2, 1, 2, 1);

    //4
    miniCuadro(100, 200, 2, 1, 1, 1);
    miniCuadro(200, 200, 2, 1, 3, 3);
    miniCuadro(300, 200, 1, 3, 4, 3);
    miniCuadro(400, 200, 2, 3, 1, 1);
    miniCuadro(500, 200, 3, 1, 2, 2);
    miniCuadro(600, 200, 2, 1, 2, 1);
    miniCuadro(700, 200, 1, 3, 3, 3);

    //5
    miniCuadro(100, 100, 1, 3, 2, 1);
    miniCuadro(200, 100, 3, 2, 3, 4);
    miniCuadro(300, 100, 1, 2, 2, 2);
    miniCuadro(400, 100, 3, 1, 3, 4);
    miniCuadro(500, 100, 3, 2, 3, 3);
    miniCuadro(600, 100, 2, 3, 1, 1);
    miniCuadro(700, 100, 2, 1, 1, 1);

    glFlush();
}

void cuadroAleatorio(void) {
    srand(time(0));//Hace que los numeros aleatorios tomen el tiempo como semilla.
    glClear(GL_COLOR_BUFFER_BIT);
    int colorCua, colorCir, rot1, rot2;
    for (int x = 100; x <= 700; x += 100) {
        for (int y = 100; y <= 500; y += 100) {
            colorCua = (rand() % 3) + 1;
            switch (colorCua) {//El color del circulo deberia de ser distinto al cuadrado
            case 1:
                colorCir = (rand() % 2) + 2;
                break;
            case 2:
                colorCir = (rand() % 2) * 2 + 1;
                break;
            case 3:
                colorCir = (rand() % 2) + 1;
            default:
                break;
            }
            if (rand() % 2 == 1) {
                rot1 = (rand() % 2) + 1;
                rot2 = (rand() % 2) + 1;
            }
            else {
                rot1 = (rand() % 2) + 3;
                rot2 = (rand() % 2) + 3;
            }
            miniCuadro(x, y, colorCua, colorCir, rot1, rot2);
        }
    }
    glFlush();
}
*/

void display(){
    double size=0.1;
    int color_square,color_circle, type_circle;
    for(double x = -0.8; x <= 0.8; x += size){
        for(double y = -0.8; y <= 0.8; y += size){
            color_square=rand() % 4;
            color_circle=rand() % 4;
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
    //glEnable(GL_BLEND); //Permite el uso de opacos
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Permite el uso de opacos
    init();
    //glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
