#version 330 core

in vec3 FragColor;
in vec2 FragTexPos;

uniform bool HasTexture = false;
uniform float Transparency = 1.f;
uniform vec3 ColorHue = vec3(0.0);
uniform sampler2D Texture;

out vec4 OutColor;

void main()
{   
	if(HasTexture == true) {
		vec4 textureVec = texture(Texture, FragTexPos);
		textureVec.a *= Transparency;
		textureVec += vec4(ColorHue, 0.0);
		OutColor = textureVec;
	}
	else{
		OutColor = vec4(FragColor, 1.0f);
	}
}