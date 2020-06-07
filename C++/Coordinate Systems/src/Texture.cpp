/*
 * Texture.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: Marcel A. Pratikto
 */

#include "Texture.h"

// variables
const GLuint textureUnit[16] = {
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

// functions
Texture::Texture(const GLchar* textureLocation) {
	// create texture object
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		// texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// minify/downscale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// magnify/upscale
		// mipmap filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// load and generate texture
	int width, height;
	unsigned char* image = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D); // mipmaps
	// unbind
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Use(Shader program, const GLchar* textureSampler, GLuint textureSamplerLocation){
	glActiveTexture(textureUnit[textureSamplerLocation]);
	glBindTexture(GL_TEXTURE_2D, texture); //use this->texture
	glUniform1i(glGetUniformLocation(program.program(), textureSampler), textureSamplerLocation);
}

