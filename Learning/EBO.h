#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>
class EBO {
public:
	// Reference ID of the Element Buffer Object
	GLuint ID;
	// Constructor that generates an Element Buffer Obj and links it to indices
	EBO(std::vector<GLuint>& indices);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};



#endif
