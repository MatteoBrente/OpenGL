#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// A VAO stores the data of a VBO in order to make it easier for OpenGL to access data
void VAO::LinkAttrib (VBO& VBO, unsigned int layout, unsigned int numComponents, unsigned int type, GLsizei stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); // Tell the VAO how to read the VBO data
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}