#version 330 core

uniform sampler2D TexSampler0;

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = texture(TexSampler0, TexCoord);
}