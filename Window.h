#pragma once

#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	~Window();

public:
	void Init(int width, int height, const char *title);

	void SetClearColor(float r, float g, float b, float a);

	void ClearWindow();

	void Render();

	void SetOpenglSettings();

	void SetViewport(float x, float y, float width, float height);

public:
	int GetWidth();
	int GetHeight();
	GLFWwindow* GetWindow();
	
private:
	int Width, Height;
	GLFWwindow *GameWindow;
};