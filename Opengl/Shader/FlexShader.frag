#version 330 core
in vec3 FragPos;
in vec3 FragColor;
in vec3 FragNormal;
in vec2 FragTexPos;

uniform vec3 CameraPos;
uniform vec3 LightPos;
uniform vec3 LightColor;
uniform bool HasTexture;

uniform float Shininess;
uniform float SpecularStrength;

uniform sampler2D Texture;

out vec4 OutColor;

float AmbientStrength = 0.3;

vec3 calculate_PointLight()
{
	vec3 viewDirection = normalize(CameraPos - FragPos);
		
	vec3 normal = normalize(FragNormal);
	vec3 lightDirection = normalize(LightPos - FragPos);
   
   	float diffuseStrength = max(dot(normal, lightDirection), 0.0);

   	vec3 diffuse = diffuseStrength * LightColor;

	vec3 ambient = AmbientStrength * LightColor;
	
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), Shininess);
	vec3 specular = SpecularStrength * spec * LightColor;
	
	if(HasTexture == true && FragPos.y > -100.0) 
	{
		vec3 textureColor = texture(Texture, FragTexPos).rgb;
		vec3 result = (ambient + diffuse + specular) * textureColor;

		return result;
	}
	else
	{
		vec3 result = (ambient + diffuse + specular) * FragColor;

		return result;
	}
}

void main()
{   	
	vec3 pointLight = calculate_PointLight();
	
   	OutColor = vec4(pointLight, 1.0f);
}