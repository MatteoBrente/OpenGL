#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "shaderClass.h"

class Texture
{
    public:
        // Reference ID of the Textures
        GLuint ID;
        // Type of the texture
        GLenum type;
        // Constructor that build the texture
        Texture (const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit (Shader& shader, const char* uniform, GLuint unit);

        void Bind();
        void Unbind();
        void Delete();
};

#endif //TEXTURE_CLASS_H