#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

out vec3 outColor;
out vec2 outTexcoord;

out vec3 outLightPos;
out vec3 outFragPos;
out vec3 outNormal;
out vec3 outViewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	gl_Position = proj * view * model * vec4(pos, 1);
	outColor = color;
	outTexcoord = texcoord;

	outFragPos = (model * vec4(pos, 1)).xyz;	
	outNormal = (model * vec4(normal, 0)).xyz;
	outLightPos = lightPos;
	outViewPos = viewPos;
}