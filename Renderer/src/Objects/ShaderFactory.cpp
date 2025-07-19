#include "ShaderFactory.h"

gpu_ptr<Shader> ShaderFactory::FromFiles(const std::string& vertexPath,
                                         const std::string& fragmentPath)
{
	std::string vertexCode, fragmentCode;
	if (!ReadFile(vertexPath, vertexCode))
	{
		LOG_ERROR("Failed to load vertex shader file: {}", vertexPath);
		return nullptr;
	}
	if (!ReadFile(fragmentPath, fragmentCode))
	{
		LOG_ERROR("Failed to load fragment shader file: {}", fragmentPath);
		return nullptr;
	}

	auto shader = make_gpu_ptr<Shader>();
	shader->SetSources(vertexCode, fragmentCode);
	shader->Load();
	return shader;
}

gpu_ptr<Shader> ShaderFactory::FromMemory(const std::string& vertexSrc,
                                          const std::string& fragmentSrc)
{
	auto shader = make_gpu_ptr<Shader>();
	shader->SetSources(vertexSrc, fragmentSrc);
	shader->Load();
	return shader;
}

bool ShaderFactory::ReadFile(const std::string& path, std::string& outContent)
{
	std::ifstream file(path);
	if (!file.is_open())
		return false;

	std::stringstream buffer;
	buffer << file.rdbuf();
	outContent = buffer.str();
	return true;
}
