#include "Utilities.h"

char* LoadTextFile(const char *path)
{
	FILE *file;
	fopen_s(&file, path, "r");

	if (!file)
	{
		std::cout << "Failed to load: " << path << std::endl;

		return NULL;
	}

	fseek(file, 0, SEEK_END);
	unsigned int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *data = new char[length + 1];
	memset(data, 0, length + 1);

	fread_s(data, length + 1, 1, length, file);

	fclose(file);

	return data;
}