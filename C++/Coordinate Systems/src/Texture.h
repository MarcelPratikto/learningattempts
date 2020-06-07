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

public:
	// constructor
	Texture(const GLchar* textureLocation);
	// other functions
	void Use(Shader program, const GLchar* textureSampler, GLuint textureSamplerLocation);	//use this->texture
};

#endif /* TEXTURE_H_ */
