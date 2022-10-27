#include "Model.h"

const unsigned int width = 800, height = 800;




int main() {
	glfwInit(); //Initialize GLFW


	

	// Tell GLFW what version of OpenGL we are using
	// Using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the core profile
	// We are using ONLY the modern functions 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFW window of X=800 and Y=800 with name 'Tesing'
	GLFWwindow* window = glfwCreateWindow(width, height, "Testing", NULL, NULL);
	// Error check the window to see if it failed to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return - 1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	// In this case, the view port goes from : x = 0,  y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	//Creates Shader obj using sahhders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	
	// Enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	// Creates the camera obj
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/bunny/scene.gltf");

	// Main while loop, keeps the window from instantly closing
	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					
		// Gets user inputs for keyboard and mouse movement
		camera.Inputs(window);
		// Updates and exports the camera matrix to the vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);
		
		// Swap the buffers
		glfwSwapBuffers(window);
		// take care of all GLFW events, ex moving the window

		glfwPollEvents();
			
	}

	
	shaderProgram.Delete();


	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}