#ifndef _EBO_CLASS_H_
#define _EBO_CLASS_H_

#include <glad/glad.h>


class EBO
{
    public:
        GLuint ID;
        
        EBO(GLuint* vertices, GLsizeiptr size);
        
        void Bind();
        void Unbind();
        void Delete();
};

#endif //_EBO_CLASS_H_