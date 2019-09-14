#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::LoadShader(const char *vertexPath, const char *fragPath)
{
	char *vShader = LoadTextFile("simple vertex.vert");
	char *fShader = LoadTextFile("simple vertex.frag");

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vShader, NULL);
	glShaderSource(fragmentShader, 1, &fShader, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	char infoLog[1024];

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	Program = glCreateProgram();

	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);

	glLinkProgram(Program);

	glGetProgramiv(Program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(Program, 1024, NULL, infoLog);

		std::cout << infoLog << std::endl;
	}
}

void Shader::ActivateShader()
{
	glUseProgram(Program);
}

unsigned int Shader::GetProgram()
{
	return Program;
}