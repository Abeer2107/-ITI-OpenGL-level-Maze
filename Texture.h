#pragma once



#include "Utilities.h"

class Texture
{
public:
	Texture();
	~Texture();

public:
	void CreateTexture(const char *path);

	void UseTexture(int index = 0);

private:
	unsigned int TextureHandle;
	int Width, Height;
};

