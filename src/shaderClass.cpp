#include "shaderClass.h"

std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Create Vertex Shader
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexFile);

	//Create Fragment Shader
	GLuint fragmentShader = CompileShader(GL_VERTEX_SHADER, fragmentFile);

	//Create Shader Program Object and get reference
	//Then add the Vertex and Fragment shaders to the program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Link all the shaders together into the program
	glLinkProgram(ID);
	//Error check for program
	compileErrors(ID,"PROGRAM");

	//Delete the now useless Vertex and Fragment Shader Objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

GLuint Shader::CompileShader(GLuint type, const char* sourceFile)
{
	//Removes null terminations from file
	std::string code = getFileContents(sourceFile);
	const char* src = code.c_str();
	
	//Create Shader Object and get reference, 
	//Then attach the source to it and compile it in machine code
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	//Error check for shader
	if (type == GL_VERTEX_SHADER)
		compileErrors(id, "VERTEX");
	else if (type == GL_FRAGMENT_SHADER)
		compileErrors(id, "FRAGMENT");
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << std::endl;
		}
	}
}