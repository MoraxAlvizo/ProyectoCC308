#include <GL/glut.h>
#include <stdio.h>

double velocidad= 10;
float angulos_caminado[2][6] ;
double movimiento_base=0.0f;

int rotate=0;

int zoom_flag=GL_FALSE,rotate_flag=GL_FALSE ;

float langle_count = 30 , // ANGULO PIERNA IZQUIERDA
      langle_count2 = 0 , // ANGULO PIERNA IZQUIERDA2
      rangle_count = -30 ,
      rangle_count2 = 0 ,
      zoom =0.0f;
      //ANGULO DE LAS PIERNAS

void TimerFunction(){
  animar_base();
  glutTimerFunc(velocidad, TimerFunction, 1);
}



void keyboard (unsigned char key, int x, int y){
  switch(key){
  case 'S' :
    if ((velocidad+1)<1000) velocidad+=1;
    break ;
  case 's' :
    if ((velocidad-1)>3) velocidad-=1;
    else{
      if ((velocidad-0.1f)>2) velocidad-=0.1f;
    }
    break ;
  case 27 :
    exit(0);
    break;
  default :
    glutIdleFunc(NULL) ;
    break ;
  }
}


void special(int key, int x, int y){
  switch (key){
  case GLUT_KEY_UP :
    zoom += 1 ;
    glutPostRedisplay() ;
    break ;
  case GLUT_KEY_DOWN :
    zoom -= 1 ;
    glutPostRedisplay() ;
    break ;
  case GLUT_KEY_LEFT :
    rotate = (rotate + 5) % 360 ;
    glutPostRedisplay() ;
    break ;
  case GLUT_KEY_RIGHT :
    rotate = (rotate - 5) % 360 ;
    glutPostRedisplay() ;
    break ;
  default :
    break ;
  }
}

//================= init () ==========================

void init(){
  const GLubyte* informacion;

   glClearColor(0, 0, 0, 0) ; // color del fondo
   glShadeModel( GL_SMOOTH) ; // aun no se que hace
   //GL_FLAT = plano

   informacion = glGetString(GL_VENDOR) ;
   //glGetString = return a string describing the current GL connection
   printf("VENDOR : %s\n", informacion) ;
   informacion = glGetString(GL_RENDERER) ;
   printf("RENDERER : %s\n", informacion) ;
   informacion = glGetString(GL_EXTENSIONS) ;
   printf("EXTENSIONS : %s\n", informacion) ;
   informacion = glGetString(GL_VERSION) ;
   printf("VERSION : %s\n", informacion) ;

   /*
GL_VENDOR

        Returns the company responsible for this GL implementation.
        This name does not change from release to release.
GL_RENDERER

        Returns the name of the renderer.
        This name is typically specific to a particular configuration of a hardware
        platform.
        It does not change from release to release.
  GL_VERSION
        Returns a version or release number.
  GL_SHADING_LANGUAGE_VERSION
        Returns a version or release number for the shading language.
        glGetStringi returns a pointer to a static string
        indexed by index.
        name can be one of the following:
  GL_EXTENSIONS
       For glGetStringi only, returns the extension string
       supported by the implementation at index.


   */

   angulos_caminado[0][3] = langle_count ;
   angulos_caminado[1][3] = rangle_count ;
   movimiento_base = mostrar_movimiento_base(langle_count,langle_count2,rangle_count,rangle_count) ;
   glutTimerFunc(velocidad, TimerFunction, 1);
}

//================= display() ========================

void display(void){

  glClear(GL_COLOR_BUFFER_BIT) ;

  glPushMatrix() ;

  glPushMatrix() ;
  glTranslatef(0.0,0.0, zoom) ;  // tran,rot = zooming
  glRotatef(rotate,0.0,1.0,0.0) ;// rot,tran = moving
  Dibuja_Base_Legs() ;
  glPopMatrix() ;

  glPopMatrix() ;

  glutSwapBuffers() ;

}

//================= reshape(w,h) =====================

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei)w, (GLsizei)h) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0) ;
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
  glTranslatef(0.0, 0.0, -5.0) ;
}

// =============== main(argc,argv) ===================

int main(int argc, char** argv){
  glutInit(&argc, argv) ;// inicializar la libreria glut
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;// inicializa el display
  glutInitWindowSize(500,500) ; // tamaño
  glutInitWindowPosition(100, 100) ;// posicion
  glutCreateWindow("Segundo Ejemplo : Piernas en movimiento") ;// creacion de una ventana
  init() ;

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
