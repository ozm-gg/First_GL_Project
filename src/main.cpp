#include <dinput.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"


GLfloat point[] = {
	0, 0.5f, 0,
	0.5f, -0.5f, 0,
	-0.5f, -0.5f, 0
};

GLfloat colors[] = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

int g_width = 1600;
int g_height = 1200;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	g_width = width;
	g_height = height;
	glViewport(0, 0, g_width, g_height);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Cant load GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "Engine", nullptr, nullptr);
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

	
	{
		ResourceManager resource_manager = ResourceManager(argv[0]);
		auto DefaultShaderProgram = resource_manager.loadShaders("Default Shaders", "res/shaders/vertex.glsl", "res/shaders/fragment.glsl");

		if (!DefaultShaderProgram)
		{
			std::cerr << "Cant create shader program" << std::endl;
		}

		GLuint points_vbo;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

		GLuint colors_vbo;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			DefaultShaderProgram->use();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
