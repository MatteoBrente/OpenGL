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
	// Create vertex shader and check if it compiled successfully
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexFile);
	compileErrors(vertexShader, "VERTEX");

	// Create fragment shader and check if it compiled successfully
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFile);
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program, then attach Vertex and Fragment and link it
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	compileErrors(program, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
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

unsigned int Shader::compileShader (unsigned int type, const char* sourceFile)
{
	// Read sourceFile and store it into a readable string
	std::string shaderCode = getFileContents(sourceFile);
	const char* shaderSource = shaderCode.c_str();

	// Create Shader Object and compile it to machine code
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	return shaderID;
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	int hasCompiled;
	char infoLog[512];

	if (type != "PROGRAM") // Error checks Vertex and Fragment Shaders
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (!hasCompiled)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << " - " << infoLog << std::endl;
		}
	}
	else // Error checks Shader Programs
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (!hasCompiled)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << " - " << infoLog << std::endl;
		}
	}
}