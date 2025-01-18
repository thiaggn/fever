#version 330 core

uniform sampler2D TexSampler;

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = texture(TexSampler, TexCoord);
}