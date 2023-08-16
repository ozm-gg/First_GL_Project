#pragma once
#include <string>
#include "glad/glad.h"

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram);
		ShaderProgram(ShaderProgram&& shaderProgram);
		bool isCompiled() const { return _isCompiled; }
		void use() const;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool _isCompiled = false;
		GLuint _ID;
	};
}
