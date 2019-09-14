#pragma once

#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Transform
{
public:
	Transform();
	~Transform();

public:
	glm::mat4 GetModelMatrix();

	glm::mat4 GetViewMatrix(glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 camUp);

	glm::mat4 GetPerspective(float fov, float aspect, float near, float far);

public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

