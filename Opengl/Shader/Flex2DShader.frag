#version 330 core

in vec3 FragColor;
in vec2 FragTexPos;

uniform bool HasTexture;
uniform sampler2D Texture;

out vec4 OutColor;

void main()
{   
	if(HasTexture == true) {
		OutColor = vec4(texture(Texture, FragTexPos).rgb, 0.0);
	}
	else{
		OutColor = vec4(FragColor, 1.0f);
	}
}