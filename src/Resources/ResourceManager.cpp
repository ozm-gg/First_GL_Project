#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Renderer/ShaderProgram.h"

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	_path = executablePath.substr(0, found);

}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName,
	const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if(vertexString.empty())
	{
		std::cerr << "No vertex shader" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = _shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if(newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Cant load shader program" << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = _shaderPrograms.find(shaderName);
	if(it != _shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Cant find shader" << std::endl;
	return nullptr;
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(_path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
	if(!f.is_open())
	{
		std::cerr << "Failed to open: " << _path + "\\" + relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
