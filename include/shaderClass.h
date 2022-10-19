#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

class Shader
{
public:
	// Reference ID of the Shader Program
	unsigned int program;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

private:
	unsigned int compileShader (unsigned int type, const char* sourceFile);
	// Check errors in the compilation of a shader or program
	void compileErrors(unsigned int shader, const char* type);
};
#endif