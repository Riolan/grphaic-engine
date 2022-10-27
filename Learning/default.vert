#version 330 core

// Positions/Coords
layout (location = 0) in vec3 aPos;
// Normals (not neccessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture coords
layout (location = 3) in vec2 aTex;


// Outputs the current pos for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coords to the frag shader
out vec2 texCoord;


// Imports the camera matrix
uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
void main() {
	
	// Calcs the current pos
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));	
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coords from the Vertex Data to "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	// Assigns the normal form the Vertex Data to "Normal"
	Normal = aNormal;

	// Outputs the pos/coords of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}
