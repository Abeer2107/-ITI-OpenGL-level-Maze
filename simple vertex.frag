#version 330

out vec4 color;

in vec3 outColor;
in vec2 outTexcoord;

in vec3 outLightPos;
in vec3 outFragPos;
in vec3 outNormal;
in vec3 outViewPos;

struct DirectionalLight
{
	vec3 Color;
	vec3 Direction;

	float Intensity;
};

uniform DirectionalLight directional;
uniform sampler2D tex;

vec3 CalculateDirectional(DirectionalLight dir, vec3 viewDir, vec3 normal)
{	
	vec3 ambientCol = dir.Intensity * dir.Color;

	vec3 lightDir = normalize(dir.Direction);
	vec3 norm = normalize(normal);
	
	float diffuseAngle = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseCol = dir.Intensity * diffuseAngle * dir.Color;

	vec3 reflected = normalize(reflect(-lightDir, norm));	
	float specAngle = max(dot(viewDir, reflected), 0);

	specAngle = pow(specAngle, 256);

	vec3 specCol = dir.Intensity * specAngle * dir.Color;

	return specCol + diffuseCol + ambientCol;
}

void main()
{
	vec3 viewDir = normalize(outViewPos - outFragPos);

	vec3 finalLight = CalculateDirectional(directional, viewDir, outNormal);
	//vec4 col = vec4(finalLight * texture(tex, outTexcoord).xyz /*vec3(0, 0.5f, 1)*/, 1);

	color = texture(tex, outTexcoord);//col;
}