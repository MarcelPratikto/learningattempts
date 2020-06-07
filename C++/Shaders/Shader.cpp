/*
 * Shader.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: Marcel A. Pratikto
 */

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

//1. Take source code from specified files and transform the contents into GLchar array
	// input file stream (to open files)
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	// strings (to hold content of opened files)
	std::string vertexCode;
	std::string fragmentCode;
	// ensure ifstream objects can THROW exceptions (badbit: read/writing error on i/o operation)
	vertexFile.exceptions(std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::badbit);
	// TRY to catch exceptions thrown by above
	try {
		// open files
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		// read shader file's buffer contents into streams
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		// close file handlers
		vertexFile.close();
		fragmentFile.close();
		//convert stream into string
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	// if try CATCHes a std::ifstream::badbit exception
	catch(const std::ifstream::failure &e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	// convert string into GLchar array
	const GLchar* glVertexCode = vertexCode.c_str();
	const GLchar* glFragmentCode = fragmentCode.c_str();

//2. Compile & check shaders
	GLuint vertex, fragment;
	//variables to check if compilation is successful/not
	GLint success;
	GLchar infoLog[512];
	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &glVertexCode, NULL);		//(shaderID, #, source, length)
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);	//(shaderID, parameter, result)
	if (!success){
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);	//(shaderID, maxLength, stringLengthOfError, log)
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
	}
	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &glFragmentCode, NULL);	//(shaderID, #, source, length)
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);	//(shaderID, parameter, result)
	if (!success){
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);	//(shaderID, maxLength, stringLengthOfError, log)
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
	}

//3. attach shaders, link & check shader program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << std::endl;
	}

//4. Delete shaders after attached to shader program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::Use(){
	glUseProgram(this->Program);
}


/*Shader::~Shader() {

}*/

