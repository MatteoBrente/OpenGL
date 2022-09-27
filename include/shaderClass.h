#ifndef _SHADER_CLASS_H_
#define _SHADER_CLASS_H_

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string getFileContents (const char* filename);

class Shader
{
    public:
        GLuint ID;
        Shader (const char* vertexFile, const char* fragmentFile);

        void Activate();
        void Delete();
};

#endif //_SHADER_CLASS_H_