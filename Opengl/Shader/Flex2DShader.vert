#version 330 core

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexPos;

out vec3 FragColor;
out vec2 FragTexPos;

void main()
{
	
	// if (gl_VertexID == 3){
	// 	FragColor = vec3(0.0);
	// }
	// else{
	// 	FragColor = aColor;	
	// }
	FragColor = aColor;
	FragTexPos = aTexPos;
    gl_Position = ProjectionMatrix * ModelMatrix * vec4(aPos.xy, 0.0, 1.0);;
}