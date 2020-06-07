/*
 * Texture.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: Marcel A. Pratikto
 */

#include "Texture.h"

Texture::Texture(const GLchar* textureLocation) {
	// create texture object
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		// texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// minify/downscale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// magnify/upscale
		// mipmaps
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//
	// load and generate texture
	int width, height;
	unsigned char* image = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// unbind
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Use(Shader program, const GLchar* textureSampler, GLuint textureSamplerLocation){
	glActiveTexture(textureUnit[textureSamplerLocation]);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program.program(), textureSampler), textureSamplerLocation);
}

