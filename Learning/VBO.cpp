#include "VBO.h"

// Constructor that generates a Vertex Buffer Obj and links it to vertices
VBO::VBO(std::vector<Vertex>& vertices) {
	glGenBuffers(1, &ID);
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
// Unbinds the VBO
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Deletes the VBO
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}
