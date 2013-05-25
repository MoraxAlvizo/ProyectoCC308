#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Mesh{
	
public:
	Mesh(char*);
	~Mesh();
	std::vector<glm::vec3> out_vertices; 
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;

	//buffers
	GLuint vertexbuffer;
	GLuint uvbuffer;

	void drawMesh(GLuint Texture, GLuint TextureID);
};

#endif