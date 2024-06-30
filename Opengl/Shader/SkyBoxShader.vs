#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 Projection;
uniform mat4 View;

out vec3 TexCoords;

void main()
{
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);
   	gl_Position = Projection * View * vec4(aPos, 1.0);
}