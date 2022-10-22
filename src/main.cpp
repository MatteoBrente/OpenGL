#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "camera.h"

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLErrorCheck(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(__FILE__, __LINE__))

// Error functions
static void GLClearErrors();
static bool GLLogCall(const char* file, int line);

//Width and height of the window
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;


// Vertices buffer, that contains the commented attributes
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.0f, 1.0f,  0.0f,     0.92f, 0.86f, 0.76f,    2.5f, 5.0f
};

// Specifies in which order to render the vertices
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using (In this is OpenGL 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile (that means we only have the modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object naming it "OpenGL_Test"
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL_Test", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD. Needs to be done after creating the context
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, WIDTH, HEIGHT);


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");


	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	// Needs to be done once per attribute (position, color, texture coord)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Assign the texture to the shader program
	Texture texture("./resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	// Enables the depth buffer (hides vertices that shouldn't be in view)
	GLErrorCheck (glEnable (GL_DEPTH_TEST));

	// Instanciate camera
	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.5f, 2.5f));

	// Main while loop	
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		GLErrorCheck (glClearColor (0.07f, 0.13f, 0.17f, 1.0f));
		// Clean the back buffer and assign the new color to it
		GLErrorCheck (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		//Include input functions in the main loop
		camera.Inputs(window);

		// Create camera matrix
		camera.Matrix(45.0f, 0.1f, 100.f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		texture.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives
		GLErrorCheck(glDrawElements(GL_TRIANGLES, (sizeof(indices) / sizeof(int)), GL_UNSIGNED_INT, 0));
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	texture.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}

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