#include "ShaderProgram.h"

#include <iostream>

Renderer::ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader)
{
	GLuint vertexShaderID, fragmentShaderID;
	if(!createShader(vertex_shader, GL_VERTEX_SHADER, vertexShaderID))
	{
		std::cout << "Vertex shader compile error:"<< std::endl;
		return;
	}
	if (!createShader(fragment_shader, GL_FRAGMENT_SHADER, fragmentShaderID))
	{
		std::cout << "Fragment shader compile error:" << std::endl;
		glDeleteShader(vertexShaderID);
		return;
	}

	_ID = glCreateProgram();
	glAttachShader(_ID, vertexShaderID);
	glAttachShader(_ID, fragmentShaderID);
	glLinkProgram(_ID);

	GLint success;
	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
		std::cout << "Link error:" << infoLog << std::endl;
		return;
	}
	else
	{
		_isCompiled = true;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

}

Renderer::ShaderProgram& Renderer::ShaderProgram::operator=(ShaderProgram&& shaderProgram)
{
	glDeleteProgram(_ID);
	_ID = shaderProgram._ID;
	_isCompiled = shaderProgram._isCompiled;

	shaderProgram._ID = 0;
	shaderProgram._isCompiled = false;

	return *this;
}

Renderer::ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)
{
	_ID = shaderProgram._ID;
	_isCompiled = shaderProgram._isCompiled;

	shaderProgram._ID = 0;
	shaderProgram._isCompiled = false;
}

Renderer::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_ID);
}

void Renderer::ShaderProgram::use() const
{
	glUseProgram(_ID);
}

bool Renderer::ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* code = source.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		std::cout << "Shader compile error:" << infoLog << std::endl;
		return false;
	}
	return true;
}
