#include "Triangles.h"


namespace triangles{
	GLfloat triangleVertex[] = {
		// position				// color			// texture pos
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// left bottom
		-1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// left top
		 1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// right top
		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f	// right bottom
	};
	GLsizeiptr triangleVertexSize() { return sizeof(triangleVertex); }

	GLuint triangleIndices[] = {
		//REMEMBER THAT ARRAYS START AT ZERO
		0, 1, 2,	// first triangle
		0, 2, 3		// second triangle
	};
	GLsizeiptr triangleIndicesSize() { return sizeof(triangleIndices); }

	GLfloat triangleVertex1[] = {
		//position				//color				//tex pos
		-0.5f,  0.0f, 0.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f,	// left triangle point
		 0.0f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f, 1.0f,	// center triangle point
		 0.5f,  0.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f	// right triangle point
	};
	GLsizeiptr triangleVertex1Size() { return sizeof(triangleVertex1); }

	// cube
	GLfloat triangleVertex2[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	GLsizeiptr triangleVertex2Size() { return sizeof(triangleVertex2); }

	// cube
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	GLsizeiptr cubePositionsSize() { return sizeof(cubePositions); }
}
