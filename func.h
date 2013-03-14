#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>

GLuint *vbo;
GLuint *vinx;

GLubyte rojo[] = {255, 0, 0, 255};
GLubyte verde[] = {0, 255, 0, 255};
GLubyte azul[] = {0, 0, 255, 255};
GLubyte blanco[] = {255, 255, 255, 255};
GLubyte negro[] = {0, 0, 0, 255};
GLubyte naranja[] = {255, 255, 0, 255};
GLubyte morado[] = {255, 0, 255, 255};
GLubyte piel[] = {253, 199, 121, 255};
GLubyte gris[] = {59, 59, 59, 255};
GLubyte pelirojo[] = {166,  14, 14, 255};
GLubyte grisBoton[] = {140, 140, 140, 255};
GLubyte grisMochila[] = {200,200,200,255};
GLubyte cafe[]={152,64,15,255};


void InitMesh() {
  unsigned int i;

  vbo = (GLuint *)malloc(OBJECTS_COUNT * sizeof(GLuint));
  vinx = (GLuint *)malloc(OBJECTS_COUNT * sizeof(GLuint));

  glGenBuffers(OBJECTS_COUNT, vbo);

  for (i=0; i<OBJECTS_COUNT; i++) {
	  glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	  glBufferData(GL_ARRAY_BUFFER, sizeof (struct vertex_struct) * vertex_count[i], &vertices[vertex_offset_table[i]], GL_STATIC_DRAW);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  glGenBuffers(OBJECTS_COUNT, vinx);
  for (i=0; i<OBJECTS_COUNT; i++) {
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vinx[i]);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indexes[0]) * faces_count[i] * 3, &indexes[indices_offset_table[i]], GL_STATIC_DRAW);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

#define BUFFER_OFFSET(x)((char *)NULL+(x))

void DrawMesh(unsigned int index, int apply_transformations) {

	if (apply_transformations) {
	  glPushMatrix();
		glMultMatrixf(transformations[index]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vinx[index]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(0));

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(3 * sizeof (float)));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(6 * sizeof (float)));

	glDrawElements(GL_TRIANGLES, faces_count[index] * 3, INX_TYPE, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (apply_transformations) {
		glPopMatrix();
	}
}

void DrawAllMeshes()
{
	unsigned int i;
    //glColor4f(1, 1, 0, 1);
	for (i=0; i<OBJECTS_COUNT; i++) {
        /*//switch para dibujar muñeca
	    switch(i){

        case PLANE_009:
            glColor4ubv(grisBoton);
            break;
        case PLANE_008:
            glColor4ubv(grisBoton);
            break;
        case PLANE_007:
            glColor4ubv(azul);
            break;
        case PLANE_006:
            glColor4ubv(grisBoton);
            break;
        case PLANE_005:
            glColor4ubv(grisBoton);
            break;
        case PLANE_004:
            glColor4ubv(grisMochila);
            break;
        case FALDA:
            glColor4ubv(gris);
            break;
        case BRAZOS :
            glColor4ubv(piel);
            break;
        case CALCETINES:
            glColor4ubv(grisMochila);
            break;
        case PLANE_003 :
            glColor4ubv(cafe);
            break;
        case BOTAS :
            glColor4ubv(cafe);
            break;
        case CUBE_004  :
            glColor4ubv(pelirojo);
            break;
        case PIERNAS :
            //glRotatef(60, 0, 0, 1);
            glColor4ubv(piel);
            break;
        case CIRCLE_010 :
            glColor4ubv(grisBoton);
            break;
        case CIRCLE_009 :
            glColor4ubv(grisBoton);
            break;
        case CIRCLE_008 :
            glColor4ubv(grisBoton);
            break;
        case CIRCLE_007 :
            glColor4ubv(grisBoton);
            break;
        case BLUSA :
            glColor4ubv(gris);
            break;
        case CUBE_002 :
            glColor4ubv(pelirojo);
            break;
        case CUBE_000 :
            glColor4ubv(blanco);//ojos
            break;
        case CIRCLE_003 :
            glColor4ubv(grisBoton);
            break;
        case CIRCLE_002 :
            glColor4ubv(grisBoton);
            break;
        case HELIX :
            glColor4ubv(naranja);
            break;
        case GORRO :
            glColor4ubv(gris);
            break;
        case CABEZA :
            glColor4ubv(piel);
            break;
        case CABELLO :
            glColor4ubv(pelirojo);
            break;
        case PLANE_001 :
            glColor4ubv(naranja);
            break;
        case PLANE :
            glColor4ubv(pelirojo);
            break;
        default: continue;

	    }*/
		DrawMesh(i, 1);
	}
}

