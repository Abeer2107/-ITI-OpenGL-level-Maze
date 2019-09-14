#include <iostream>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Vertex.h"
#define boxSize 0.2
float boardX = 1.25, boardY = 0.1, boardZ = 1.2;
bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, hitBox = false;
bool checkCollision(glm::vec3 player, float objx, float objy, float objz) {
	bool collisionX = player.x + 0.19 >= objx + 0.5 && player.x <= objx + boxSize + 0.5;
	//bool collisionY = player.y >= obj.y && obj.y + boxSize >= player.y;
	bool collisionZ = player.z + 0.19 >= objz + 0.5 && player.z <= objz + boxSize + 0.5;
	//std::cout << player.x << "," << player.y << "," << player.z << " " << obj.x << "," << obj.y << "," << obj.z << " " << collisionX << "," << collisionZ << std::endl;
	return collisionX && /*collisionY &&*/ collisionZ;
}
void main(){
	//Window////////////////////////////////////////// 
	Window window;
	window.Init(700, 700, "Opengl");
	//Shader//////////////////////////////////////////
	Shader shader;
	shader.LoadShader("simple shader.vert", "simple shader.frag");
	shader.ActivateShader();
	//Textures//////////////////////////////////////////
	Texture tex;
	tex.CreateTexture("container.jpg");
	Texture blockTex;
	blockTex.CreateTexture("block.jpg");
	Texture targetTex;
	targetTex.CreateTexture("Target.jpg");
	Texture ballTex;
	ballTex.CreateTexture("rock.jpg");
	//Camera//////////////////////////////////////////
	glm::vec3 camPos(0.0f, -2.0f, -5.0f);
	glm::vec3 camTarget(0.0f, 0.0f, 1.0f);
	glm::vec3 camUp(0.0f, 3.0f, 0.0f);
	//Board//////////////////////////////////////////
	Mesh board = board.CreateCuboid(glm::vec3(0.0f), glm::vec3(boardX, boardY, boardZ), glm::vec2(1.0f), true);
	Transform boardTrans;
	boardTrans.Position = glm::vec3(0.0f, 0.0f, 0.5f);
	boardTrans.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	boardTrans.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	//Obstacles//////////////////////////////////////
	Mesh ob1 = Mesh::CreateCuboid(glm::vec3(0.5f, -0.1f, 0.0f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh ob2 = Mesh::CreateCuboid(glm::vec3(0.1f, -0.1f, 0.2f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh ob3 = Mesh::CreateCuboid(glm::vec3(0.1f, -0.1f, 0.4f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh ob4 = Mesh::CreateCuboid(glm::vec3(-0.3f, -0.1f, -0.2f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh ob5 = Mesh::CreateCuboid(glm::vec3(0.3f, -0.1f, -0.2f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh ob6 = Mesh::CreateCuboid(glm::vec3(-0.3f, -0.1f, -0.45f), glm::vec3(boxSize), glm::vec2(1.0f), true);
	Mesh target = Mesh::CreateCuboid(glm::vec3(0.5, -0.05, -0.2), glm::vec3(0.2,0.01,0.2), glm::vec2(1.0f), true);
	//Sphere?////////////////////////////////////////
	Mesh player = Mesh::CreateSphere(glm::vec3(-0.5f, -0.1f, 0.0f), glm::vec3(0.07f), glm::vec2(1.0f), true);
	Transform playerTrans;
	playerTrans.Position = glm::vec3(-0.5f, -0.15f, 0.0f);
	playerTrans.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	playerTrans.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	////////////////////////////////////////////////
	unsigned int uniformTexture = glGetUniformLocation(shader.GetProgram(), "tex");
	unsigned int uniformModel = glGetUniformLocation(shader.GetProgram(), "model");
	unsigned int uniformView = glGetUniformLocation(shader.GetProgram(), "view");
	unsigned int uniformProj = glGetUniformLocation(shader.GetProgram(), "proj");	
	unsigned int uniformLightPos = glGetUniformLocation(shader.GetProgram(), "lightPos");
	unsigned int uniformViewPos = glGetUniformLocation(shader.GetProgram(), "viewPos");
	unsigned int uniformDirColor = glGetUniformLocation(shader.GetProgram(), "directional.Color");
	unsigned int uniformDirectionDir = glGetUniformLocation(shader.GetProgram(), "directional.Direction");
	unsigned int uniformDirInten = glGetUniformLocation(shader.GetProgram(), "directional.Intensity");
	////////////////////////////////////////////
	glm::vec3 playerPos(0.0f, 0.0f, 0.0f);	
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, -1.0f);
	////////////////////////////////////////////
	int counter = 0;
	float value = 0;
	int FPS = 0;
	int UPS = 0;
	double lastTime = glfwGetTime();
	double elapsedTime = 0;
	double tmp = 0;
	float t = 1.0f / 60.0f;		
	double currentTime;

	while (!glfwWindowShouldClose(window.GetWindow())){
		FPS++;
		currentTime = glfwGetTime();
		elapsedTime += currentTime - lastTime;
		tmp += currentTime - lastTime;
		lastTime = currentTime;		
		while (elapsedTime >= t){
			// Updating			
			UPS++;	
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_X) == GLFW_PRESS) { glfwSetWindowShouldClose(window.GetWindow(), 1); }
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) { moveUp = true;	}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) { moveDown = true;	}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) { moveLeft = true;	}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) { moveRight = true; }
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS){ camPos.x -= 0.5f * t; /*camTarget.x += 0.3f * t;*/}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS){ camPos.x += 0.5f * t; /*camTarget.x -= 0.3f * t;*/}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS){ camPos.y -= 0.5f * t; /*camTarget.y -= 0.3f * t;*/}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS){ camPos.y += 0.5f * t; /*camTarget.y += 0.3f * t;*/}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_Q) == GLFW_PRESS){ camPos.z += 0.5f * t; /*camTarget.y += 0.1f * t;*/}
			if (glfwGetKey(window.GetWindow(), GLFW_KEY_E) == GLFW_PRESS){ camPos.z -= 0.5f * t; /*camTarget.y += 0.1f * t;*/}
			
			if (moveUp) {
				if (playerPos.z < boardZ - 0.2f) {
					playerPos.z += 0.01;
				}
				else
					moveUp = false;
			}

			if (moveDown) {
				if (playerPos.z > 0.0f) {
					playerPos.z -= 0.01;
				}
				else
					moveDown = false;
			}

			if (moveRight) {
				if (playerPos.x < boardX - 0.2f) {
					playerPos.x += 0.01;
				}
				
				else
					moveRight = false;
			}

			if (moveLeft) {
				if (playerPos.x > 0.0f) {
					playerPos.x -= 0.01;
				}	
				else
					moveLeft = false;
			}

			if (checkCollision(playerPos, 0.5f, -0.1f, 0.0f) || checkCollision(playerPos, 0.1f, -0.1f, 0.2f) || checkCollision(playerPos, 0.1f, -0.1f, 0.4f)
				|| checkCollision(playerPos, -0.3f, -0.1f, -0.2f) || checkCollision(playerPos, 0.3f, -0.1f, -0.2f) || checkCollision(playerPos, -0.3f, -0.1f, -0.45f)) {
				if (moveUp) { moveUp = false; playerPos.z -= 0.01; }
				else if (moveRight) { moveRight = false; playerPos.x -= 0.01; }
				else if (moveLeft) { moveLeft = false; playerPos.x += 0.01; }
				else if (moveDown) { moveDown = false; playerPos.z += 0.01; }
			}

			if (checkCollision(playerPos, 0.5, -0.05, -0.2)) {
				playerPos.x = 0.0; playerPos.z = 0.0;
				moveUp = false; moveDown = false; moveRight = false; moveLeft = false;
			}
				
			elapsedTime -= t;
		}
		// Rendering		
		window.ClearWindow();
		shader.ActivateShader();
		glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(boardTrans.GetModelMatrix()));
		glUniformMatrix4fv(uniformView, 1, false, glm::value_ptr(boardTrans.GetViewMatrix(camPos, camTarget, camUp)));
		glUniformMatrix4fv(uniformProj, 1, false, glm::value_ptr(boardTrans.GetPerspective(50, 1, 0.1f, 1000)));
		glUniform3f(uniformLightPos, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(uniformViewPos, camPos.x, camPos.y, camPos.z);
		glUniform3f(uniformDirColor, 1, 1, 1);
		glUniform3f(uniformDirectionDir, lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(uniformDirInten, 0.5f);
		//Board///////////////////////////
		tex.UseTexture();
		glUniform1i(uniformTexture, 0);
		board.Draw();
		//Obstacles///////////////////////
		blockTex.UseTexture(1);
		glUniform1i(uniformTexture, 1);
		ob1.Draw(); ob2.Draw(); ob3.Draw(); ob4.Draw();	ob5.Draw(); ob6.Draw();
		targetTex.UseTexture(2);
		glUniform1i(uniformTexture, 2);
		target.Draw();
		//////////////////////////////////
		ballTex.UseTexture(3);
		glUniform1i(uniformTexture, 3);
		playerTrans.Position = playerPos;
		glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(playerTrans.GetModelMatrix()));
		glUniformMatrix4fv(uniformView, 1, false, glm::value_ptr(playerTrans.GetViewMatrix(camPos, camTarget, camUp)));
		glUniformMatrix4fv(uniformProj, 1, false, glm::value_ptr(playerTrans.GetPerspective(50, 1, 0.1f, 1000)));
		player.Draw();
		/////////////////////////////////
		shader.ActivateShader();
		if (tmp >= 1){ tmp = 0; UPS = 0; FPS = 0; }		
		window.Render();
	}
	glfwTerminate();
}