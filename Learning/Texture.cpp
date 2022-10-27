#include "Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot) {

	// Assigns the type of the texture of the texture obj
	type = texType;


	// Get the width, height, and the number of color channels of the img
	int widthImg, heightImg, numColCh;
	// flips the img (stbi reads it upside down)
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture obj
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// Configures the type of algorithm that is used to make the img smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// CConfigures the way the texture repeats
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines incase you use GL_CLAMP_TO_BORDER
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTextParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	if (numColCh == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColCh == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	else
		throw std::invalid_argument("Automatic Texture type recognition failed.");

	// Generates MipMaps (smaller images of the orginal img)
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL texture obj
	stbi_image_free(bytes);
	// Unbinds the OpenGL texture so it can't be accidentally modified
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// Gets the locations of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activate before changing the value of a uniform
	shader.Activate();
	glUniform1i(texUni, unit);

}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Delete() {
	glDeleteTextures(1, &ID);
}

