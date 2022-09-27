#ifndef _VAO_CLASS_H_
#define _VAO_CLASS_H_

#include <glad/glad.h>
#include "VBO.h"


class VAO
{
    public:
        GLuint ID;
        
        VAO();
        
        void LinkVBO(VBO VBO, GLuint layout);
        void Bind();
        void Unbind();
        void Delete();
};

#endif //_VAO_CLASS_H_