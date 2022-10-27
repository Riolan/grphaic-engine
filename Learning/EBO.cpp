#include "EBO.h"



// Constructor that generates an Element Buffer Obj and links it to indices
EBO::EBO(std::vector<GLuint>& indices) {
	glGenBuffers(1, &ID);
	// Bind the EBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Introduce the vertices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}
//Binds the EBO
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
// Unbinds the EBO
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
// Deletes the EBO
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}
