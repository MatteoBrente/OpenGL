#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	unsigned int ID;

	VAO();

	void LinkAttrib (VBO& VBO, unsigned int layout, unsigned int numComponents, unsigned int type, GLsizei stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};

#endif