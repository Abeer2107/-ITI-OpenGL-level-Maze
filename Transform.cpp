#include "Transform.h"
#include<iostream>


Transform::Transform(){}
Transform::~Transform(){}

glm::mat4 Transform::GetModelMatrix(){
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), Position);
	//std::cout << Position.x << "," << Position.y << "," << Position.z << std::endl;
	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

	return trans * (rotX * rotY * rotZ) * scale;
}

glm::mat4 Transform::GetViewMatrix(glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 camUp){
	return glm::lookAt(camPos, camTarget, camUp);
}

glm::mat4 Transform::GetPerspective(float fov, float aspect, float near, float far){
	return glm::perspective(fov, aspect, near, far);
}