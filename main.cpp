

#include <windows.h>
#include <mmsystem.h>
//-------------------------------------------------------------------------
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>


#include "CargadorObj.h"
#include "CargadorTextura.h"


#include <cmath>
#include "Camera.h"
#include <time.h>

#include <math.h>
#include <string.h>


#define PI 3.1415926536

using namespace std;


//importante
static float ypoz = 0, zpoz = 0;

//Mouse
float Xmouse = 0;
float Ymouse = 0;



//--------------------------------------------------------



Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
int g_viewport_width = 1000;
int g_viewport_height = 700;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;
const float g_translation_speed = 0.01;
const float g_rotation_speed = PI / 180 * 0.25;
////////////////////////////////////////////////////


////////CARGAR//MODELOS//////////////////////////////////////////////

//PUNTERO

///////////////////////////////////////

//////////CAMARA ///////////
float c_x =0;
float c_y =0;
float c_z =0;

float a_x =0;
float a_y =0;
float a_z =0;



 void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	texturatexpiso();
	texturaArbol();


	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}





void camaracord(){

    //poscicion
    c_x=g_camera.m_x;
    c_y=g_camera.m_y;
    c_z=g_camera.m_z;

    //punto de vista
    a_x =g_camera.m_lx;
    a_y =g_camera.m_ly;
    a_z =g_camera.m_lz;



};


void graficar(void){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    g_camera.Refresh();
    camaracord();

    cout<< "Camara:  "<<c_x<<"  "<<c_y<<"  "<<c_z<<"  ";
    cout<< "      Punto de vision:  "<<a_x<<"  "<<a_y<<"  "<<a_z<<endl;



	glTranslatef(100,2.5,40);

	 glPushMatrix(); //LOZAS
            glBindTexture(GL_TEXTURE_2D, texpiso[0].texID);
            glmDraw(piso, GLM_SMOOTH | GLM_TEXTURE);

            glPushMatrix();

            glBindTexture(GL_TEXTURE_2D, texarbol[0].texID);
            glmDraw(arbol_tronco, GLM_SMOOTH | GLM_TEXTURE);

            glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texarbol[1].texID);
            glmDraw(arbol_hojas, GLM_SMOOTH | GLM_TEXTURE);
            glPopMatrix();



            glPopMatrix();


    glPopMatrix(); //FIN LOZAS


	glutSwapBuffers();


}
void redimensionar(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80,16.0/9.0,1,185);

}
void animate(int i){
    ypoz += 0.03;
    if (ypoz > 360) ypoz = 0;
    glutPostRedisplay();
    glutTimerFunc(2, animate, 1);
}


/////colisiones//////
void limite(){




        //gran techo
      //  g_camera.colision(18, 192, -50, 134, varaltura, 40);


}

void Timer(int value){


    if (g_fps_mode) {
        if (g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed);
        }
        else if (g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        else if (g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if (g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        else if (g_mouse_left_down) {
            g_camera.Fly(-g_translation_speed); //g_mouse_left_down
        }
        else if (g_mouse_right_down) {
            g_camera.Fly(g_translation_speed); //g_mouse_right_down
        }
    }




    glutTimerFunc(1, Timer, 0);


}

void Idle(){
    graficar();
}
void KeyboardUp(unsigned char key, int x, int y){
    g_key[key] = false;
}
void Keyboard(unsigned char key, int x, int y){

    if (key == 27) {
        exit(0);
    }

    if (key == ' ') {
        g_fps_mode = !g_fps_mode;

        if (g_fps_mode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
            std::cout << "presionado";
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }

    g_key[key] = true;






}


void MouseMotion(int x, int y){
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if (just_warped) {
        just_warped = false;
        return;
    }

    if (g_fps_mode) {
        int dx = x - g_viewport_width / 2;
        int dy = y - g_viewport_height / 2;

        if (dx) {
            g_camera.RotateYaw(g_rotation_speed * dx);

        }

        if (dy) {
            g_camera.RotatePitch(g_rotation_speed * dy);
        }

        glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

        just_warped = true;
    }
}
void Mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("AvanceT4Proyecto");
    init();


//cargas Modelos
    CargaPiso();
    CargaArbol();
////////////////

 /////camara
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MouseMotion);
    glutKeyboardFunc(Keyboard);


    glutKeyboardUpFunc(KeyboardUp);
    glutIdleFunc(Idle);
    glutTimerFunc(1, Timer, 0);
    glutIdleFunc(graficar);
    glutIdleFunc(limite);



    glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
	glutTimerFunc(2, animate, 1);
	glutMainLoop();






    //glEnable(GL_LIGHT0);
    //glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHTING);



	return 0;
}

