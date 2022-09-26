#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>	

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	
	//Initialize GLFW, then tell it what version and profile we're using
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordinates of the triangle's vertices
	GLfloat vertices[]
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //bottom left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //bottom right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //top
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //center left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //center right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, //bottom center
	};

	GLuint indices[]
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	//Create a GLFW window of 800 * 800 pixels
	GLFWwindow* window{ glfwCreateWindow(800, 800, "OpenGL_Test", NULL, NULL) };
	
	//Check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce window to current context
	glfwMakeContextCurrent(window);

	//Load glad and specify the window viewport
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//Create Vertex Shader Object and get reference
	//Then attach the source to it and compile it in machine code
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get reference, 
	//Then attach the source to it and compile it in machine code
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create Shader Program Object and get reference
	//Then add the Vertex and Fragment shaders to the program
	GLuint shaderProgram{ glCreateProgram() };
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all the shaders together into the program
	glLinkProgram(shaderProgram);

	//Delete the now useless Vertex and Fragment Shader Objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Get reference containers for the Vertex Array and Vertex Buffer Objects
	GLuint VAO, VBO, EBO;

	//Generate VAO and VBO with one obj each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind our VAO as the current Vertex Array Object
	glBindVertexArray(VAO);

	//Bind our VBO as an array buffer, then introduce the vertices into it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Configure the VA so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind VAO and VBO to 0 so we don't accidentaly use modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Set new background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which programs we want to use
		glUseProgram(shaderProgram);
		//Bind the VAO
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//Delete all objects we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//Close window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}