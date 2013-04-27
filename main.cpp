#include <stdio.h>
#include <stdlib.h>
// Funcion el git en windows
#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <sys/time.h>

#include "town.h"
#include "func.h"

int windowwidth;
int windowheight;
float rotateSpeed = 60.0f; /* degrees per second */
int pause = False;
int zoom = 45;

void SetUpOpenGL();
void SetUpLights();
void DrawScene(float );
float GetTimeInterval();
void Resize(int , int);


int main (int argc, char *argv[]) {
	SDL_Event evento;
	SDLKey key;
	float x = 0.0, y = 0.0, z = -5.0;
	int rotar = 0;
	float t, T = 0.0;
	int cnt = 0;


	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		fprintf (stderr, "Falló al inicializar SDL\n");
		return 1;
	}

	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	if (SDL_SetVideoMode (640, 480, 16, SDL_OPENGL) == NULL) {
		fprintf (stderr, "Falló la inicialización del video\n");
		return 1;
	}
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY ,SDL_DEFAULT_REPEAT_INTERVAL);
	SetUpOpenGL();
	InitMesh();
	GetTimeInterval();

	float radio = (float) 640 / (float) 480;
	gluPerspective (60.0, radio, 1.0, 1024.0);


	do {
		while (SDL_PollEvent (&evento) > 0) {
			switch (evento.type) {
				case SDL_QUIT:
					SDL_Quit ();
					return 0;
					break;
				case SDL_KEYDOWN:
					key = evento.key.keysym.sym;
					/* Eventos de teclas aquí */
					switch(key){

                        case SDLK_RIGHT:
                            x++;
                            break;
                        case SDLK_LEFT:
                            x--;
                            break;
                        case SDLK_UP:
                            y++;
                            break;
                        case SDLK_DOWN:
                            y--;
                            break;
                        case SDLK_a:
                            z++;
                            break;
                        case SDLK_s:
                            z--;
                        case SDLK_r:
                            rotar = (rotar + 1) % 360;
                            break;
                        case SDLK_z:
                            zoom++;
                            break;
                        case SDLK_x:
                            zoom--;
                            break;
                        case SDLK_SPACE:
                            pause = !pause;
                            break;
                        default: x = x;

					}
					break;
			}
		} /* Procesar eventos */
        Resize(640,480);
        T += (t = GetTimeInterval());
        DrawScene(t);
        glFlush();
		SDL_GL_SwapBuffers ();
		SDL_Delay (32);
		cnt++;
        if (T > 1.0) {
          printf("%f\n", (float) cnt / T);
          T = 0.0;
          cnt = 0;
        }
	} while (1);
	return 0;
}

void SetUpOpenGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float) windowwidth / (float) windowheight, 0.15, 210.0);
  glViewport(0, 0, windowwidth, windowheight);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  //glColor4f(1, 1, 1, 1);
}

void SetUpLights() {
  float pos[] = {10, 10, 10, 0};
  float ambient[] = {0.3, 0.3, 0.3, 1};
  float white[] = {1, 1, 1, 1};

  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glEnable(GL_LIGHT0);
}


void DrawScene(float dT) {
  static float angle = 0.0f;
  glClearColor(0, 0, 0, 0);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 10, 10, 0, 0, 0, 0, 0, 1); /* Up direction is Z-axis... like in Blende ;-) */

  SetUpLights();

  if (!pause)
    angle += rotateSpeed * dT;
  glTranslatef(0.0,-5.0,-5.0);
  glRotatef(angle, 0, 0, 1);
  DrawAllMeshes();
}

float GetTimeInterval() {
  static struct timeval time = {0, 0};
  static struct timeval last = {0, 0};
  int sec, usec;


  gettimeofday(&time, NULL);

  sec = time.tv_sec - last.tv_sec;
  usec = time.tv_usec - last.tv_usec;


  last.tv_sec = time.tv_sec;
  last.tv_usec = time.tv_usec;

  sec *= 1000000;
  sec += usec;

  return (float) sec / 1.0e6;
}

void Resize(int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(zoom, (float) width / (float) height, 0.15, 251.0);
  glViewport(0, 0, width, height);
}
