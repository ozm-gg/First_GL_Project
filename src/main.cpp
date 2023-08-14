
#include <dinput.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_width = 1600;
int g_height = 1200;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    g_width = width;
    g_height = height;
    glViewport(0,0,g_width,g_height);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(void)
{
	if (!glfwInit())
	{
		std::cout << "Cant load GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallBack);

	glfwMakeContextCurrent(window);


	if (!gladLoadGL())
	{
		std::cout << "Cant load GLAD" << std::endl;
		return -1;
	}


	std::cout << "Renderer" << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;

	glClearColor(1, 1, 0, 1);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
