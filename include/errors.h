#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLErrorCheck(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(__FILE__, __LINE__))


static void GLClearErrors() 
{
	// Deletes all previous errors
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* file, int line)
{
	// Create an error object and print it for each GL error
	// Needs to be a bool in order to crash the application if an error is found
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error " << error << "] At: " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}