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
	//Create Shader Program Object
	program = glCreateProgram();

	//Create Vertex Shader
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexFile);
	//Create Fragment Shader
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentFile);

	//Then add the Vertex and Fragment shaders to the program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//Link all the shaders together into the program
	glLinkProgram(program);
	glValidateProgram(program);

	//Error check for program
	compileErrors(program,"PROGRAM");

	//Delete the now useless Vertex and Fragment Shader Objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(program);
}

void Shader::Delete()
{
    glDeleteProgram(program);
}

unsigned int Shader::CompileShader(unsigned int type, const char* sourceFile)
{
	//Create Shader Object
	unsigned int id = glCreateShader(type);

	//Removes null terminations from file
	std::string code = getFileContents(sourceFile);
	const char* src = code.c_str();
	
	//Attach the source to it and compile it in machine code
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error check for shader
	if (type == GL_VERTEX_SHADER)
		compileErrors(id, "VERTEX");
	else if (type == GL_FRAGMENT_SHADER)
		compileErrors(id, "FRAGMENT");
	
	return id;
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	int hasCompiled;
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