#pragma once

#include "Utilities.h"

class Shader
{
public:
	Shader();
	~Shader();

public:
	void LoadShader(const char *vertexPath, const char *fragPath);

	void ActivateShader();

public:
	unsigned int GetProgram();

private:
	unsigned int Program;
};

