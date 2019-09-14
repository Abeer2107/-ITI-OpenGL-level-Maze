#pragma once

#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

struct Vertex
{
	Vertex(glm::vec3 p = glm::vec3(0.0f)
		, glm::vec3 c =  glm::vec3(0.0f)
		, glm::vec2 t =  glm::vec2(0.0f)
		, glm::vec3 n =  glm::vec3(0.0f))
	{
		pos = p;
		color = c;
		texcoord = t;
		normal = n;
	}

	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};