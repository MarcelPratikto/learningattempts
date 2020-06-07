//============================================================================
// Name        : Texture First Try.cpp
// Author      : Marcel Pratikto
// Version     :
// Copyright   : Your copyright notice
// Description : test out what you learned
//============================================================================

// GLEW
#include <GL/GLEW.h>
// GLFW
#include <GLFW/GLFW3.h>
// SOIL
#include <SOIL.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// other preprocessors
#include <iostream> // std::cout, std::cin, etc.
#include "Shader.h"
#include "Texture.h"
#include "triangles.h"


// GLOBAL VARIABLES
	// glfw window
GLuint WIDTH = 800, HEIGHT = 600;

	// texture layer brightness
GLfloat mixAlpha = 0.2f;

	// movement
float g_movement_x = 0.0f;
float g_movement_y = 0.0f;

// FORWARD DECLARATION
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); //glfw input control
void translate(glm::mat4 *transformation);

using namespace std;

int main() {
// GLFW
	cout << "GLFW" << endl;
	glfwInit(); // initialize
	// GLFW WINDOW HINTS
	// use openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// use openGL core profile(disables openGL legacy functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// disable resizing window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// GLFW WINDOW OBJECT
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr){
		cerr << "Failed to create GLFW window. " << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// GLFW INPUT CONTROL
	glfwSetKeyCallback(window, key_callback);

// GLEW
	cout << "GLEW" << endl;
	glewExperimental = GL_TRUE; // use openGL core functionality instead of legacy
	glewInit();

// OPENGL VIEWPORT
	cout << "VIEWPORT" << endl;
	glViewport(0, 0, WIDTH, HEIGHT);

// Shaders
	cout << "SHADER" << endl;
	Shader shader0("C:/C++ Programs/Shaders/vertexShader.txt", "C:/C++ Programs/Shaders/fragmentShader.txt");
	Shader shader1("C:/C++ Programs/Shaders/vertexShader.txt", "C:/C++ Programs/Shaders/fragmentShader.txt");

// Textures
	cout << "TEXTURE" << endl;
	Texture container_wood("C:/C++ Programs/Textures/container_wood.jpg");
	Texture wall("C:/C++ Programs/Textures/wall.jpg");
	Texture awesomeface("C:/C++ Programs/Textures/awesomeface.png");

// Vertex Array Object, Vertex Buffer Object, Element Buffer Object
	cout << "VAO, VBO, EBO" << endl;
	GLuint VAOtotal = 2;
	GLuint VBOtotal = 2;
	GLuint EBOtotal = 1;
	GLuint VAO[VAOtotal], VBO[VBOtotal], EBO[EBOtotal]; // ID
	// generate
	glGenVertexArrays(VAOtotal, VAO); // (size, buffer)
	glGenBuffers(VBOtotal, VBO);
	glGenBuffers(EBOtotal, EBO);
		// VAO[0]
		glBindVertexArray(VAO[0]);
			// VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //(mode, id)
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangles::triangleVertex), triangles::triangleVertex, GL_STATIC_DRAW); //(mode, size, data, usage)
			// EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles::triangleIndices), triangles::triangleIndices, GL_STATIC_DRAW);
			// (attribute, # of components per vertex attribute, type, normalized, stride, start position of attribute)
				// attribute position
			glEnableVertexAttribArray(0); // enable attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
				// attribute color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
				// attribute texture position
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
			// unbind
			//glBindBuffer(GL_ARRAY_BUFFER, 0); //VBO
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // never unbind EBO, it will make drawing vertex order obsolete
			glBindVertexArray(0); //VAO
		// VAO[1]
		glBindVertexArray(VAO[1]);
			// VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangles::triangleVertex1), triangles::triangleVertex1, GL_STATIC_DRAW);
			// (attribute, # of components per vertex attribute, type, normalized, stride, start position of attribute)
				// attribute position
			glEnableVertexAttribArray(0); // enable attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
				// attribute color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
				// attribute texture position
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
			//unbind
			glBindVertexArray(0);

// GAME LOOP
	cout << "GAME LOOP" << endl;
	while(!glfwWindowShouldClose(window)){ // checks if glfw has been instructed to close

		// GLFW INPUT CONTROL
		glfwPollEvents(); // check for mouse and keyboard inputs and will call recommended functions via glfwSetKeyCallback

		// CLEAR SCREEN
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set GL_COLOR_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		// DRAW TRIANGLE
		shader1.Use();
			// texture layer
		wall.Use(shader1, "textureSampler", 0);
			// position & transformations
		glm::mat4 transformation1;
		glUniformMatrix4fv(glGetUniformLocation(shader1.program(), "transformation"), 1, GL_FALSE, glm::value_ptr(transformation1));
			//
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// DRAW ELEMENTS
		shader0.Use();
			// texture layer 0 container_wood
		container_wood.Use(shader0, "textureSampler", 0);
			// texture layer 1 awesomeface
		awesomeface.Use(shader0, "textureSampler1", 1);
			// alpha of texture (mixAlpha)
		glUniform1f(glGetUniformLocation(shader0.program(), "mixAlpha"), mixAlpha);
			// position & transformations
		glm::mat4 transformation;
		translate(&transformation);
		transformation = glm::rotate(transformation, (GLfloat)glfwGetTime() * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "transformation"), 1, GL_FALSE, glm::value_ptr(transformation));
			//
		glBindVertexArray(VAO[0]); // bind VAO
		//glDrawArrays(GL_TRIANGLES, 0, 3); // without EBO (one triangle only)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // using EBO (two triangles making a rectangle)
		//glBindVertexArray(0); // unbind VAO

		// DRAW ELEMENTS 1
		//shader0.Use();
			// texture layer 0 container_wood
		wall.Use(shader0, "textureSampler", 0);
			// texture layer 1 awesomeface
		awesomeface.Use(shader0, "textureSampler1", 1);
			// alpha of texture (mixAlpha)
		glUniform1f(glGetUniformLocation(shader0.program(), "mixAlpha"), mixAlpha);
			// position & transformations
		glm::mat4 transformation2;
		transformation2 = glm::translate(transformation2, glm::vec3(0.5f, 0.5f, 0.0f));
		//transformation2 = glm::rotate(transformation2, (GLfloat)glfwGetTime() + 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		GLfloat scaleAmount = sin(glfwGetTime());
		transformation2 = glm::scale(transformation2, glm::vec3(scaleAmount, scaleAmount, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "transformation"), 1, GL_FALSE, glm::value_ptr(transformation2));
			//
		//glBindVertexArray(VAO[0]); // bind VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // unbind VAO

		// DOUBLE BUFFER
		glfwSwapBuffers(window); // switch the back render buffer into the screen buffer (the one displayed on the screen)
	}

// Delete resources
	cout << "DELETE RESOURCES" << endl;
	glDeleteVertexArrays(VAOtotal, VAO);
	glDeleteBuffers(VBOtotal, VBO);
	glDeleteBuffers(EBOtotal, EBO);
	glfwTerminate(); // glfw

// End of program
	return 0;
}


// CONTROLS
void translate(glm::mat4 *transformation){
	*transformation = glm::translate(*transformation, glm::vec3(g_movement_x, g_movement_y, 0.0f));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		g_movement_y += 0.1;

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		g_movement_y -= 0.1;

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		g_movement_x -= 0.1;

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		g_movement_x += 0.1;

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		mixAlpha += 0.1;

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		mixAlpha -= 0.1;
}
