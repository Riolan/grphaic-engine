#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 textUV;
};

class VBO {
	public:
		// Reference ID of the Vertex Buffer Object
		GLuint ID;
		// Constructor that generates a Vertex Buffer Obj and links it to vertices
		VBO(std::vector<Vertex>& vertices);

		// Binds the VBO
		void Bind();
		// Unbinds the VBO
		void Unbind();
		// Deletes the VBO
		void Delete();
};



#endif