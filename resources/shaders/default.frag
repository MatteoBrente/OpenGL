#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

// The fragment shader gets called once for each pixel
// That means that operations shouldn't be done here, but in the vertex shader
void main()
{
   FragColor = texture(tex0, texCoord);
}