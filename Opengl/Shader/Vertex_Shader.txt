#version 330 core

uniform mat4 ModelMatrix;
uniform mat4 PositionMatrix;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 FragPos;
out vec3 FragColor;
out vec3 FragNormal;

void main()
{
	FragPos = vec3(PositionMatrix * vec4(aPos, 1.0));
	FragNormal = aNormal;
	FragColor = aColor;	
   	gl_Position = ModelMatrix * vec4(aPos, 1.0);
}