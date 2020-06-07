/*
 * Texture.h
 *
 *  Created on: Apr 9, 2016
 *      Author: Marcel A. Pratikto
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/GLEW.h>	// GLEW for required OpenGL headers
#include <SOIL.h>		// SOIL
#include "Shader.h"

class Texture {
protected:
	// ID
	GLuint texture;

	// variables
	GLuint textureUnit[16] = {
		GL_TEXTURE0,
		GL_TEXTURE1,
		GL_TEXTURE2,
		GL_TEXTURE3,
		GL_TEXTURE4,
		GL_TEXTURE5,
		GL_TEXTURE6,
		GL_TEXTURE7,
		GL_TEXTURE8,
		GL_TEXTURE9,
		GL_TEXTURE10,
		GL_TEXTURE11,
		GL_TEXTURE12,
		GL_TEXTURE13,
		GL_TEXTURE14,
		GL_TEXTURE15
	};

public:
	// constructor
	Texture(const GLchar* textureLocation);
	// other functions
	void Use(Shader program, const GLchar* textureSampler, GLuint textureSamplerLocation);	//use this->texture
};

#endif /* TEXTURE_H_ */
