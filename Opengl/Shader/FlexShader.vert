#version 330 core

uniform mat4 ModelMatrix;
uniform mat4 PositionMatrix;
uniform bool InstancedRendering = false;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexPos;
layout (location = 4) in mat4 InstancedMatrix;

out vec3 FragPos;
out vec3 FragColor;
out vec3 FragNormal;
out vec2 FragTexPos;

void main()
{
	if (InstancedRendering == true)
	{
		FragPos = vec3(InstancedMatrix * vec4(aPos, 1.0));
		FragNormal = normalize(mat3(transpose(inverse(InstancedMatrix))) * aNormal);
		FragColor = aColor;	
		FragTexPos = aTexPos;
   		gl_Position = ModelMatrix * InstancedMatrix *vec4(aPos, 1.0);
	}
	else
	{
		FragPos = vec3(PositionMatrix * vec4(aPos, 1.0));
		FragNormal = normalize(mat3(transpose(inverse(PositionMatrix))) * aNormal);
		FragColor = aColor;	
		FragTexPos = aTexPos;
   		gl_Position = ModelMatrix * vec4(aPos, 1.0);
	}
}