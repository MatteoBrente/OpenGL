#include "shaderClass.h"

std::string getFileContents (const char* filename)
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

Shader::Shader (const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode {getFileContents(vertexFile)};
    std::string fragmentCode {getFileContents(fragmentFile)};

    const char* vertexSource {vertexCode.c_str()};
    const char* fragmentSource {fragmentCode.c_str()};

	//Create Vertex Shader Object and get reference
	//Then attach the source to it and compile it in machine code
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get reference, 
	//Then attach the source to it and compile it in machine code
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//Create Shader Program Object and get reference
	//Then add the Vertex and Fragment shaders to the program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Link all the shaders together into the program
	glLinkProgram(ID);

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