/*
 * Shader.h
 *
 *  Created on: Mar 24, 2016
 *      Author: Marcel A. Pratikto
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/GLEW.h>//GLEW for required OpenGL headers

class Shader {
protected:
	// ID
	GLuint Program;
public:
	// constructor reads and builds shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// other functions
	void Use();	//use this->Program
	GLuint program();
};

#endif //SHADER_H_
