/*
 * Triangles.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Marcel A. Pratikto
 */

#ifndef TRIANGLES_H_
#define TRIANGLES_H_


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

namespace triangles{
	extern GLfloat triangleVertex[];
	extern GLsizeiptr triangleVertexSize();

	extern GLuint triangleIndices[];
	extern GLsizeiptr triangleIndicesSize();

	extern GLfloat triangleVertex1[];
	extern GLsizeiptr triangleVertex1Size();

	extern GLfloat triangleVertex2[];
	extern GLsizeiptr triangleVertex2Size();

	extern glm::vec3 cubePositions[];
	extern GLsizeiptr cubePositionsSize();
}


#endif /* TRIANGLES_H_ */
