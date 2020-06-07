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

namespace triangles{
	GLfloat triangleVertex[] = {
		// position				// color			// texture pos
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// left bottom
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// left top
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// right top
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f	// right bottom
	};
	GLuint triangleIndices[] = {
		//REMEMBER THAT ARRAYS START AT ZERO
		0, 1, 2,	// first triangle
		0, 2, 3		// second triangle
	};

	GLfloat triangleVertex1[] = {
		//position				//color				//tex pos
		 0.0f,  0.0f, 0.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f,	//left
		 0.5f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f, 1.0f,	//center
		 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f	//right
	};
}


#endif /* TRIANGLES_H_ */
