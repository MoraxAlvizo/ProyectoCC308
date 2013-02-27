#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define PI 3.141592f

bool click;
int raton[2];

class Bola {
public:
   float pos[3], vel[2];
   int toques, record, timer;
   char puntos[40];
   bool pausa;

   void Pintar() {
      glPushMatrix();
      glTranslatef(pos[0],pos[1],pos[2]);
      glColor3f(1,1,1);
      glBegin(GL_TRIANGLE_FAN);
         glVertex3f(0,0,1);
         for (float i = 0; i <= (2*PI)+0.2f; i += 0.2f ) glVertex3f(50*cosf(i),50*sinf(i),1);
      glEnd();
      glPopMatrix();
      glRasterPos2f(50,10);
      sprintf(puntos,"Toques: %i. Record: %i.", toques,record);
      for (int i = 0; i<strlen(puntos); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, puntos[i]);
   }

   void Iniciar() {
      pos[0] = pos[1] = 300;
      pos[2] = timer = toques = 0;
      vel[0] = vel[1] = 25;
      pausa = 1;
   }

   void Tocar(float x, float y) {
      if ( sqrt( pow(x-pos[0],2) + pow(y-pos[1],2) ) <= 50 && click) {
         timer = click = 0;
         toques++;
         if (record < toques) record = toques;
         vel[0] = pos[0] - x;
         vel[1] = fabs(pos[1] - y);
         pausa = 0;
      }
   }

   void Avanzar() {
      if (!pausa) {
         timer++;
         if (pos[0] > 750 || pos[0] < 50) vel[0] = -vel[0];
         pos[0] += vel[0]*3 / 10;
         pos[1] += (vel[1]*3 - timer) / 10;
      }
   }

   void Perder() {
      if (pos[1] < 50) Iniciar();
   }
} ball;

void PintarEscena() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0,800,0,600,-1,1);

   glColor3f(0,0,0.1f);
   glRectf(0,0,800,600);

   ball.Pintar();

      glutSwapBuffers();
}

void ReProyectar(int w, int h) {
   glutReshapeWindow(800,600);
   glViewport(0, 0, w, h);

      PintarEscena();
}

void Mover(int value) {
   glutTimerFunc(16,Mover,1);
   glutPostRedisplay();

   ball.Tocar(raton[0],raton[1]);
   ball.Avanzar();
   ball.Perder();
}

void Raton(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) click = 1;
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) click = 0;
   raton[0] = x;
   raton[1] = 600 - y;
}

void RatonMov(int x, int y) {
   raton[0] = x;
   raton[1] = 600 - y;
}

int main(int argc, char **argv) {
      glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(40,40);
     glutCreateWindow("Toke por HarZe");

   ball.Iniciar();

     glutReshapeFunc(ReProyectar);
   glutDisplayFunc(PintarEscena);
   glutMouseFunc(Raton);
   glutMotionFunc(RatonMov);
   glutPassiveMotionFunc(RatonMov);
     glutTimerFunc(16,Mover,1);

     glutMainLoop();
   return 0;
}
