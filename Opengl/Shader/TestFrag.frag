#version 330 core

in vec3 FragPos;
in vec3 FragColor;
in vec3 FragNormal;
in vec2 FragTexPos;

uniform sampler2D Texture;

out vec4 OutColor;

void main()
{
    OutColor = texture(Texture, FragTexPos);
}