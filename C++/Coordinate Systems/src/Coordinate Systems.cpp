//============================================================================
// Name        : Coordinate Systems.cpp
// Author      : Marcel Pratikto
// Version     :
// Copyright   :
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
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// other preprocessors
#include <iostream> // std::cout, std::cin, etc.
#include "Shader.h"
#include "Texture.h"
#include "triangles.h"


// GLOBAL VARIABLES
	// time
GLfloat g_time = 0.0f;

	// deltaTime (for hardware consistencies)
GLfloat g_deltaTime = 0.0f;			// time between current frame and last frame
GLfloat g_lastFrameTime = 0.0f;		// time of last frame

	// glfw window
GLuint WIDTH = 800, HEIGHT = 600;
	// FOV
GLfloat g_FOV = 45.0f;
GLfloat g_aspectRatio = (GLfloat)WIDTH/(GLfloat)HEIGHT;

	// texture layer brightness
GLfloat g_mixAlpha = 0.2f;

	// camera/movement/keyboard related
glm::mat4 viewMatrix;
glm::vec3 g_cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 g_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);		// unit front of cameraPosition
glm::vec3 g_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 g_cameraSide = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
bool g_firstMouse = true;
GLfloat g_lastX = WIDTH/2.0f;
GLfloat g_lastY = HEIGHT/2.0f;
GLfloat g_yaw = 0.0f;
GLfloat g_pitch = 0.0f;
GLfloat g_roll = 0.0f;

	// keyboard
bool keys[1024];


// FORWARD DECLARATION
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // GLFW input control
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); // GLFW input control
void key_pressed_action();
void setViewMatrix();
void setViewMatrixAlternate( glm::vec3 eye, float pitch, float yaw);


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
		// mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
		// keyboard
	glfwSetKeyCallback(window, key_callback);

// GLEW
	cout << "GLEW" << endl;
	glewExperimental = GL_TRUE; // use openGL core functionality instead of legacy
	glewInit();

// OPENGL VIEWPORT
	cout << "VIEWPORT" << endl;
	glViewport(0, 0, WIDTH, HEIGHT);

// Enable certain OpenGL functionality
	//glEnable(GL_DEPTH_TEST);	// z-buffer/depth buffer ENABLED IN GAME LOOP

// Shaders
	cout << "SHADER" << endl;
	Shader shader0("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt"); // rectangles
	Shader shader1("Shaders/vertexShaderTriangleUI.txt", "Shaders/fragmentShader.txt"); // triangle UI
	Shader shader2("Shaders/vertexShaderCube.txt", "Shaders/fragmentShaderCube.txt"); // cube

// Textures
	cout << "TEXTURE" << endl;
	Texture container_wood("Textures/container_wood.jpg");
	Texture wall("Textures/wall.jpg");
	Texture awesomeface("Textures/awesomeface.png");
	Texture mysteryForest("Textures/mysteryForest.jpg");
	Texture mysteryShack("Textures/mysteryShack.jpg");
	Texture GF_Carnival("Textures/GF_Carnival.png");

// Vertex Array Object, Vertex Buffer Object, Element Buffer Object
	cout << "VAO, VBO, EBO" << endl;
	GLuint VAOtotal = 3;
	GLuint VBOtotal = 3;
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
			glBufferData(GL_ARRAY_BUFFER, triangles::triangleVertexSize(), triangles::triangleVertex, GL_STATIC_DRAW); //(mode, size, data, usage)
			// EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles::triangleIndicesSize(), triangles::triangleIndices, GL_STATIC_DRAW);
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
			glBufferData(GL_ARRAY_BUFFER, triangles::triangleVertex1Size(), triangles::triangleVertex1, GL_STATIC_DRAW);
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
			glBindVertexArray(0);
		// VAO[2]
		glBindVertexArray(VAO[2]);
			// VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, triangles::triangleVertex2Size(), triangles::triangleVertex2, GL_STATIC_DRAW);
			// (attribute position, # of components per vertex attribute, type, normalized, stride, start position of attribute)
				// attribute position
			glEnableVertexAttribArray(0); // enable attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
				// attribute texture position
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
			//unbind
			glBindVertexArray(0);

// GAME LOOP
	cout << "GAME LOOP" << endl;
	while(!glfwWindowShouldClose(window)){ // checks if glfw has been instructed to close

	// TIME
		g_time = (GLfloat)glfwGetTime();

	// DELTA TIME
		g_deltaTime = g_time - g_lastFrameTime;
		g_lastFrameTime = g_time;

	// GLFW INPUT CONTROL
		glfwPollEvents(); // check for mouse and keyboard inputs and will call recommended functions via glfwSetKeyCallback
		key_pressed_action();

	// CLEAR SCREEN
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set GL_COLOR_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

	// Enable certain OpenGL functionality
		glEnable(GL_DEPTH_TEST);	// z-buffer/depth buffer
	// CLEAR depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// FOV / projection matrix
		glm::mat4 projectionMatrix;
		projectionMatrix = glm::perspective(glm::radians(g_FOV), g_aspectRatio, 0.1f, 100.0f); //(FOV, aspect ratio, front limit z-axis, back limit z-axis)
	// camera / view matrix (NOTE: glm::lookAt translates everything else by -cameraPosition)
		setViewMatrix();
		//setViewMatrixAlternate(g_cameraPosition, g_pitch, g_yaw);

	// Skybox  TODO
	shader0.Use();
		// Back
			// texture layer
		mysteryForest.Use(shader0, "textureSampler", 0);
			// projection matrix
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			// view matrix
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		// draw
		glBindVertexArray(VAO[0]);
			// model matrix
			glm::mat4 modelSkybox;
			modelSkybox = glm::translate(modelSkybox, glm::vec3(0.0f, 0.0f, g_cameraPosition.z - 25.0f));
			modelSkybox = glm::scale(modelSkybox, glm::vec3(20.0f, 20.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelSkybox));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// unbind
		glBindVertexArray(0);

	shader0.Use();
		// Right
			// texture layer
		GF_Carnival.Use(shader0, "textureSampler", 0);
			// projection matrix
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			// view matrix
		glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		// draw
		glBindVertexArray(VAO[0]);
			// model matrix
			glm::mat4 modelSkyboxRight;
			modelSkyboxRight = glm::translate(modelSkyboxRight, glm::vec3(g_cameraPosition.x + 25.0f, 0.0f, 0.0f));
			modelSkyboxRight = glm::rotate(modelSkyboxRight, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			modelSkyboxRight = glm::scale(modelSkyboxRight, glm::vec3(20.0f, 20.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader0.program(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelSkyboxRight));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// unbind
		glBindVertexArray(0);


	// cube
	shader2.Use();
			// texture layer 0 container_wood
		container_wood.Use(shader2, "textureSampler", 0);
			// texture layer 1 awesomeface
		awesomeface.Use(shader2, "textureSampler1", 1);
			// alpha of texture (g_mixAlpha)
		glUniform1f(glGetUniformLocation(shader2.program(), "mixAlpha"), g_mixAlpha);
			// projection matrix
		glUniformMatrix4fv(glGetUniformLocation(shader2.program(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			// view matrix
		glUniformMatrix4fv(glGetUniformLocation(shader2.program(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		// draw
		glBindVertexArray(VAO[2]); // bind VAO
		for (unsigned int iii = 0; iii < triangles::cubePositionsSize()/sizeof(glm::vec3); ++iii){
			// model matrix
			glm::mat4 model3;
			model3 = glm::translate(model3, triangles::cubePositions[iii]);
			/*GLfloat random = 0.0f;
			if (iii % 3 == 0)
				random = g_time * glm::radians(20.0f) * (iii + 1);
			else
				random = glm::radians(20.0f) * (iii + 1);
			model3 = glm::rotate(model3, random, glm::vec3(0.0f, 0.0f, 0.0f));*/
			glUniformMatrix4fv(glGetUniformLocation(shader2.program(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model3));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// unbind
		glBindVertexArray(0); // unbind VAO

	// disable depth
	glDisable(GL_DEPTH_TEST);

	// DRAW TRIANGLE UI
	shader1.Use();
			// texture layer
		wall.Use(shader1, "textureSampler", 0);
			// position & transformations
		glm::mat4 transformation1;
		transformation1 = glm::translate(transformation1, glm::vec3(0.75f, 0.75f, 0.0f));
		transformation1 = glm::scale(transformation1, glm::vec3(0.2f, 0.2f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader1.program(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(transformation1));
			// draw
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// unbind
		glBindVertexArray(0);

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


// CONTROLS TODO
void mouse_callback(GLFWwindow* window, double xpos, double ypos){

	// fixes large sudden jump whenever the window first receives focus of the mouse cursor
	if (g_firstMouse){
		g_lastX = xpos;
		g_lastY = ypos;
		g_firstMouse = false;
	}

	// difference in mouse position, x-axis (aiming mouse left = camera left, vice-versa)
	GLfloat xOffset = xpos - g_lastX;
	// difference in mouse position, y-axis (aiming mouse up = camera up, vice-versa)
		// NOTE: moving mouse up results in negative value for ypos,
		// hence the need to subtract the last position by the new position in order to switch the direction the camera moves in the y-axis
	GLfloat yOffset = g_lastY - ypos;
	//GLfloat yOffset = ypos - g_lastY; // difference in mouse position, y-axis reversed (aiming mouse down = camera up, vice-versa)
	g_lastX = xpos;
	g_lastY = ypos;

	GLfloat sensitivity = 0.09f; // controls mouse movement speed
	xOffset *= sensitivity;
	yOffset *= sensitivity * 0.75f;

	// degrees the camera moves up/down around the x-axis
	g_pitch += yOffset;
	// degrees the camera moves around the y-axis
	g_yaw += xOffset;
}

// try to make own view matrix based off of glm::lookat
glm::mat4 customLookAt(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 upAxis){
	glm::vec3 frontAxis = cameraPosition - cameraTarget;
	frontAxis = glm::normalize(frontAxis);

	glm::vec3 sideAxis = glm::cross(upAxis, frontAxis);
	sideAxis = glm::normalize(sideAxis);

	/*OpenGL reads by mat4[column][row]
	so: (what you see in a graph - http://learnopengl.com/#!Getting-started/Camera, scroll down to "Look At")
		mat4={	Rx, Ry, Rz, 0,
			 	Ux, Uy, Uz, 0,
			 	Fx, Fy, Fz, 0,
			 	0, 0, 0, 1}
	becomes: (in OpenGL)
		mat4={	Rx, Ux, Fx, 0,
				Ry, Uy, Fy, 0,
				Rz, Uz, Fz, 0,
				0, 0, 0, 1}
			 */
	glm::mat4 lookAt;
	lookAt = glm::mat4(
				glm::vec4(sideAxis.x, upAxis.x, frontAxis.x, 0.0f),
				glm::vec4(sideAxis.y, upAxis.y, frontAxis.y, 0.0f),
				glm::vec4(sideAxis.z, upAxis.z, frontAxis.z, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
			);

	glm::mat4 cameraPosMat;
	cameraPosMat = glm::mat4(
					glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), // negative to move vectors
					glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), // against camera position
					glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), // to simulate movement
					glm::vec4(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z, 1.0f)
				);

	lookAt = lookAt * cameraPosMat;

	return lookAt;
}

void rotation(GLfloat angle, glm::vec3 &axis, glm::vec3 &vectorToRotate){
	glm::quat rotationQuat = glm::angleAxis(glm::radians(angle), axis);
	vectorToRotate = glm::rotate(rotationQuat, vectorToRotate);
}

void setViewMatrix(){	//TODO
	/*	move the camera direction based on a matrix, no quaternions
	 * glm::mat4 cameraRotation;
	cameraRotation = glm::rotate(cameraRotation, glm::radians(-g_roll), glm::vec3(0.0f, 0.0f, 1.0f));	//rotate left/right
	cameraRotation = glm::rotate(cameraRotation, glm::radians(-g_yaw), glm::vec3(0.0f, 1.0f, 0.0f));	//look left/right
	cameraRotation = glm::rotate(cameraRotation, glm::radians(g_pitch), glm::vec3(1.0f, 0.0f, 0.0f));	//look up/down

	glm::vec4 tempUp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	tempUp = cameraRotation * tempUp;
	glm::vec3 up = glm::vec3(tempUp.x, tempUp.y, tempUp.z);
	g_cameraUp = glm::normalize(up);

	glm::vec4 tempFront = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	tempFront = cameraRotation * tempFront;
	glm::vec3 front = glm::vec3(tempFront.x, tempFront.y, tempFront.z);
	g_cameraFront = glm::normalize(front);*/


	if (g_pitch != 0.0f){
		glm::vec3 sideAxis = glm::cross(g_cameraFront, g_cameraUp);

		glm::vec3 up = g_cameraUp;
		rotation(g_pitch, sideAxis, up);
		g_cameraUp = glm::normalize(up);

		glm::vec3 front = g_cameraFront;
		rotation(g_pitch, sideAxis, front);
		g_cameraFront = glm::normalize(front);

		g_pitch = 0.0f;
	}
	if (g_yaw != 0.0f){
		/*glm::vec3 up = g_cameraUp;
		rotation(-g_yaw, g_cameraUp, up);
		g_cameraUp = glm::normalize(up);*/

		glm::vec3 front = g_cameraFront;
		rotation(-g_yaw, g_cameraUp, front);
		g_cameraFront = glm::normalize(front);

		g_yaw = 0.0f;
	}
	if (g_roll != 0){
		glm::vec3 up = g_cameraUp;
		rotation(g_roll, g_cameraFront, up);
		g_cameraUp = glm::normalize(up);

		g_roll = 0.0f;
	}

	// viewMatrix custom
	viewMatrix = customLookAt(g_cameraPosition, g_cameraPosition + g_cameraFront, g_cameraUp);

	/*// viewMatrix based on glm::lookAt
	 * //glm::mat4 viewMatrix;
	viewMatrix =	glm::lookAt(
						g_cameraPosition,					// camera position (world space)
						g_cameraPosition + g_cameraFront,	// camera target (world space)
						g_cameraUp							// up vector (world space)
					);*/
}

void setViewMatrixAlternate( glm::vec3 eye, float pitch, float yaw){
    // If the pitch and yaw angles are in degrees,
    // they need to be converted to radians. Here
    // I assume the values are already converted to radians.
    float cosPitch = cos(glm::radians(pitch));
    float sinPitch = sin(glm::radians(pitch));
    float cosYaw = cos(glm::radians(-yaw));
    float sinYaw = sin(glm::radians(-yaw));

    glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
    glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    viewMatrix = {
    		glm::vec4(       xaxis.x,            yaxis.x,            zaxis.x,      0 ),
			glm::vec4(       xaxis.y,            yaxis.y,            zaxis.y,      0 ),
			glm::vec4(       xaxis.z,            yaxis.z,            zaxis.z,      0 ),
			glm::vec4( -dot( xaxis, eye ), -dot( yaxis, eye ), -dot( zaxis, eye ), 1 )
    };
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	// close window
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

// action for key pressed from key_callback
void key_pressed_action(){
	// camera / movement
		GLfloat cameraSpeed = 10.0f * g_deltaTime;
		if (keys[GLFW_KEY_W])
			g_cameraPosition += glm::normalize(g_cameraFront) * cameraSpeed;
		if (keys[GLFW_KEY_S])
			g_cameraPosition -= glm::normalize(g_cameraFront) * cameraSpeed;
		if (keys[GLFW_KEY_A])
			g_cameraPosition -= glm::normalize(glm::cross(g_cameraFront, g_cameraUp)) * cameraSpeed;
		if (keys[GLFW_KEY_D])
			g_cameraPosition += glm::normalize(glm::cross(g_cameraFront, g_cameraUp)) * cameraSpeed;

	//camera roll (around the z-axis) TODO
		GLfloat cameraRollSpeed = 50.0f * g_deltaTime; //in degrees
		if (keys[GLFW_KEY_LEFT]){
			/*if (g_pitch < 90.0f)
				g_roll -= cameraRollSpeed;
			else if (g_pitch > 90.0f && g_pitch < 270.0f)
				g_roll += cameraRollSpeed;
			else*/
				g_roll -= cameraRollSpeed;
		}
		if (keys[GLFW_KEY_RIGHT]){
			/*if (g_pitch < 90.0f)
				g_roll += cameraRollSpeed;
			else if (g_pitch > 90.0f && g_pitch < 270.0f)
				g_roll -= cameraRollSpeed;
			else*/
				g_roll += cameraRollSpeed;
		}

	// texture alpha
		if (keys[GLFW_KEY_LEFT_BRACKET])
			g_mixAlpha += 0.1;
		if (keys[GLFW_KEY_RIGHT_BRACKET])
			g_mixAlpha -= 0.1;

	// aspect ratio & FOV
		if (keys[GLFW_KEY_MINUS]){
			if (keys[GLFW_KEY_LEFT_SHIFT])
				g_aspectRatio = 1.0f;
			else{
				if (g_FOV >= 30.0f)
					g_FOV -= 10.0f;
			}
		}
		if (keys[GLFW_KEY_EQUAL]){
			if (keys[GLFW_KEY_LEFT_SHIFT])
				g_aspectRatio = 16.0f/8.0f;
			else{
				if (g_FOV <= 80.0f)
					g_FOV += 10.0f;
			}
		}
		if (keys[GLFW_KEY_BACKSPACE]){
			if (keys[GLFW_KEY_LEFT_SHIFT])
				g_aspectRatio = (GLfloat)WIDTH/(GLfloat)HEIGHT;
		}
}
