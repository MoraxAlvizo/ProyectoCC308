#include "Camara.hpp"

Camara::Camara(GLuint programID, string id)
{

	this->id = id;
	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, id.c_str());

	//property Camara
	location = glm::vec3(4,3,-3);
	looking  = glm::vec3(0,0,0);
	position = glm::vec3(0,1,0);

	// Model matrix : an identity matrix (model will be at the origin)
	Model      = glm::mat4(1.0f);

	this->updateCamara();

}

GLfloat* Camara::getCamara(){
	return &this->MVP[0][0];
}

GLuint Camara::getMatrixID(){
	return MatrixID;
}

void Camara::updateCamara(){
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	View       = glm::lookAt(
						location, 
						looking, 
						position 
							);
	
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

}

void Camara::moveCamarato(GLint x, GLint y, GLint z){

	location = glm::vec3( x, y, z);
	this->updateCamara();

}

void Camara::watchTo(GLint x, GLint y, GLint z){

	looking = glm::vec3( x, y, z);
	this->updateCamara();

}

