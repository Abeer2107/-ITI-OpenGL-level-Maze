#include "Window.h"

Window::Window()
{
}


Window::~Window()
{
}

void Window::Init(int width, int height, const char *title)
{
	glewExperimental = true;

	if (!glfwInit())
	{
		std::cout << "failed to initialize glfw\n";

		system("pause");

		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	GameWindow = glfwCreateWindow(
		width,
		height,
		title,
		NULL,
		NULL
	);

	Width = width;
	Height = height;

	if (GameWindow == NULL)
	{
		std::cout << "Failed to create window\n";
	}

	glfwMakeContextCurrent(GameWindow);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to intialize glew\n";
	}

	char *version = (char*)glGetString(GL_VERSION);

	std::cout << version << std::endl;

	SetOpenglSettings();
}

void Window::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Window::ClearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Render()
{
	glfwSwapBuffers(GameWindow);
	glfwPollEvents();
}

void Window::SetOpenglSettings()
{
	glViewport(0, 0, Width, Height);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void Window::SetViewport(float x, float y, float width, float height)
{
	glViewport(x, y, width, height);
}

int Window::GetWidth() { return Width; }
int Window::GetHeight() { return Height; }
GLFWwindow* Window::GetWindow() { return GameWindow; }
