#pragma once
#include <map>
#include <memory>
#include <string>

#include "../Renderer/ShaderProgram.h"


class ResourceManager
{
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap _shaderPrograms;
	std::string _path;
	std::string getFileString(const std::string& relativeFilePath) const;
};
