/*
 * Base-sdl-gl.c
 * This file is part of Curso SDL
 *
 * Copyright (C) 2013 - Félix Arreola Rodríguez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//Para compilar
// gcc `pkg-config --cflags --libs gl glu` `sdl-config --cflags --libs`

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLubyte rojo[] = {255, 0, 0, 255};
GLubyte verde[] = {0, 255, 0, 255};
GLubyte azul[] = {0, 0, 255, 255};
GLubyte blanco[] = {255, 255, 255, 255};
GLubyte negro[] = {0, 0, 0, 255};
GLubyte naranja[] = {255, 255, 0, 255};
GLubyte morado[] = {255, 0, 255, 255};

GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
GLfloat v7[] = { -1.0f,  1.0f, -1.0f };

int main (int argc, char *argv[]) {
	SDL_Event evento;
	SDLKey key;
	
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
	
	/* Configurar openGL */
	glShadeModel (GL_SMOOTH);
	glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
	glClearColor (0, 0, 0, 0);
	
	glViewport (0, 0, 640, 480);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
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
					break;
			}
		} /* Procesar eventos */
		
		
		/* Aquí hacer el dibujado con openGL */
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		
		glTranslatef (0.0, 0.0, -5.0);
		
		glBegin (GL_TRIANGLES);
		glColor4ubv (rojo);
		glVertex3fv (v0);
		
		glColor4ubv (verde);
		glVertex3fv (v1);
		
		glColor4ubv (azul);
		glVertex3fv (v2);
		
		glEnd ();
		
		SDL_GL_SwapBuffers ();
		SDL_Delay (32);
	} while (1);
	return 0;
}

