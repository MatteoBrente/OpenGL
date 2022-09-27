#ifndef _VBO_CLASS_H_
#define _VBO_CLASS_H_

#include <glad/glad.h>


class VBO
{
    public:
        GLuint ID;
        
        VBO(GLfloat* vertices, GLsizeiptr size);
        
        void Bind();
        void Unbind();
        void Delete();
};

#endif //_VBO_CLASS_H_