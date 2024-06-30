#version 330 core

out vec4 OutColor;

in vec3 TexCoords;

uniform samplerCube Skybox;

void main()
{
    OutColor = texture(Skybox, TexCoords);
}