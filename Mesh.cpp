#include "Mesh.h"
#include<vector>
#define PI 3.14159265359
#define sphereDensity 100
Mesh::Mesh(){}
Mesh::~Mesh(){}

void Mesh::Draw(){
	glBindVertexArray(VertexArrayObject);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
}

Mesh Mesh::CreateMesh(Vertex *vertices, unsigned verticesCount
	, unsigned int *indices, unsigned int indicesCount, bool useNormals)
{
	if (useNormals)	{
		CalculateNormals(vertices, verticesCount, indices, indicesCount);
	}

	// Buffer handle
	unsigned int vertexBuffer;
	unsigned int elementBuffer;

	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray);

	// Generate a handle
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);

	// Bind the buffer to begin using it

	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	// Fill the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticesCount, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicesCount, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0
		, 3
		, GL_FLOAT
		, false
		, sizeof(Vertex)
		, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1
		, 3
		, GL_FLOAT
		, false
		, sizeof(Vertex)
		, (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2
		, 2
		, GL_FLOAT
		, false
		, sizeof(Vertex)
		, (void*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3
		, 3
		, GL_FLOAT
		, false
		, sizeof(Vertex)
		, (void*)((2 * sizeof(glm::vec3)) + sizeof(glm::vec2)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Mesh m;
	m.VertexBuffer = vertexBuffer;
	m.ElmentBuffer = elementBuffer;
	m.VertexArrayObject = vertexArray;
	m.IndexCount = indicesCount;

	return m;
}

Mesh Mesh::CreateCuboid(glm::vec3 pos, glm::vec3 size, glm::vec2 texScale, bool withNormals){

	Vertex vertices[24] =
	{
		// Up
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 1.0f * texScale.y)), // Top left

		// Down
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 1.0f * texScale.y)), // Top left

		// Back
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0 * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1 * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1 * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0 * texScale.x, 1.0f * texScale.y)), // Top left

		// Front																					 
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 1.0f * texScale.y)), // Top left

		// Left side																				  			
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x - (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 1.0f * texScale.y)), // Top left

		// Right side																							
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 0.0f * texScale.y)), // Bottom left
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y - (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 0.0f * texScale.y)), // Bottom right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z + (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(1.0f * texScale.x, 1.0f * texScale.y)), // Top Right
		Vertex(glm::vec3(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f), pos.z - (size.z / 2.0f)), glm::vec3(1.0f), glm::vec2(0.0f * texScale.x, 1.0f * texScale.y)), // Top left			
	};

	unsigned int indices[36] =
	{
		// Up, Front, Left ==> (0, 1, 2), (0, 2, 3)
		// Down, Back, Right ==> (2, 1, 0), (3, 2, 0)

		// Down, Back, Right = Reverse(Up, Front, Left)

		// Up
		0, 1, 2,
		0, 2, 3,

		// Down
		2 + 4, 1 + 4, 0 + 4,
		3 + 4, 2 + 4, 0 + 4,

		// Back
		2 + 8, 1 + 8, 0 + 8,
		3 + 8, 2 + 8, 0 + 8,

		// Front
		0 + 12, 1 + 12, 2 + 12,
		0 + 12, 2 + 12, 3 + 12,

		// Left side
		0 + 16, 1 + 16, 2 + 16,
		0 + 16, 2 + 16, 3 + 16,

		// Right side
		2 + 20, 1 + 20, 0 + 20,
		3 + 20, 2 + 20, 0 + 20,

	};

	Mesh shape = CreateMesh(vertices, 24, indices, 36, withNormals);

	return shape;
}

Mesh Mesh::CreateSphere(glm::vec3 pos, glm::vec3 size, glm::vec2 texScale, bool withNormals){
	std::vector<Vertex> vertVector;
	std::vector<std::vector<Vertex>> vec;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indecies;

	glm::vec2 texCoord;

	double theta, phi;
	for (int i = 0; i < sphereDensity; i++) {
		theta = i * (PI / sphereDensity);
		vertVector.clear();
		if (i % 2 == 0) texCoord.x = 0.0f * texScale.x;
		else texCoord.x = 1.0f * texScale.x;
		for (int j = -sphereDensity; j < sphereDensity; j++) {
			if (abs(j) % 2 == 0) texCoord.y = 0.0f * texScale.y;
			else texCoord.y = 1.0f * texScale.y;
			phi = j * (PI / sphereDensity);
			vertVector.insert(vertVector.begin() + (j + sphereDensity), Vertex(glm::vec3((sin(theta)*cos(phi)*size.x)+pos.x, (sin(theta)*sin(phi)*size.x)+pos.y, (cos(theta)*size.x))+pos.z, glm::vec3(1.0f), texCoord));
		}
		vec.insert(vec.begin() + i, vertVector);
	}

	int x, y;
	for (int i = 1; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size() - 1; j++) {
			x = i; y = j;
			indecies.push_back(x*vec[i].size() + y);
			y = j + 1;
			indecies.push_back(x*vec[i].size() + y);
			x = i - 1; y = j;
			indecies.push_back(x*vec[i].size() + y);
			
			x = i; y = j + 1;
			indecies.push_back(x*vec[i].size() + y);
			x = i - 1;  y = j + 1;
			indecies.push_back(x*vec[i].size() + y);
			x = i - 1; y = j;
			indecies.push_back(x*vec[i].size() + y);
		}
	}
		
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			vertices.insert(vertices.begin()+ (i * vec[i].size() + j), vec[i][j]);
		}
	}

	Mesh shape = CreateMesh(vertices.data(), vertices.size(), indecies.data(), indecies.size(), withNormals);

	return shape;
}

void Mesh::CalculateNormals(Vertex *vertices, unsigned verticesCount
	, unsigned int *indices, unsigned int indicesCount)
{
	for (int i = 0; i < indicesCount; i += 3)
	{
		int i0 = indices[i + 0];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 v1 = vertices[i1].pos - vertices[i0].pos;
		glm::vec3 v2 = vertices[i2].pos - vertices[i0].pos;

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		vertices[i0].normal += normal;
		vertices[i1].normal += normal;
		vertices[i2].normal += normal;
	}

	for (int i = 0; i < indicesCount; i++)
	{
		vertices[indices[i]].normal = glm::normalize(vertices[indices[i]].normal);
	}
}

