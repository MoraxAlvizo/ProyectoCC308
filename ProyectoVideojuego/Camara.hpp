#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Camara{

public:
	//Constructor and destructor
	Camara(GLuint , string);
	~Camara();
	glm::mat4 MVP;
	string id;

protected:
	GLuint MatrixID;
	glm::mat4 Projection;
	glm::mat4 View ;
	glm::mat4 Model;

	//property Camara
	glm::vec3 location;
	glm::vec3 looking;
	glm::vec3 position;

//metodos
public:
	GLfloat* getCamara();
	GLuint getMatrixID();
	void updateCamara();
	void moveCamarato(GLint, GLint, GLint);
	void watchTo(GLint, GLint, GLint);
};

#endif