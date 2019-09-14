#pragma once

#include "Utilities.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	void Draw();

public:
	static Mesh CreateMesh(Vertex *vertices, unsigned verticesCount
		, unsigned int *indices, unsigned int indicesCount, bool useNormals = true);

	static Mesh CreateCuboid(glm::vec3 pos, glm::vec3 size, glm::vec2 texScale, bool withNormals);
	static Mesh CreateSphere(glm::vec3 pos, glm::vec3 size, glm::vec2 texScale, bool withNormals);

private:
	static void CalculateNormals(Vertex *vertices, unsigned verticesCount
		, unsigned int *indices, unsigned int indicesCount);

private:
	unsigned int VertexBuffer;
	unsigned int ElmentBuffer;
	unsigned int VertexArrayObject;

	int IndexCount;

};



