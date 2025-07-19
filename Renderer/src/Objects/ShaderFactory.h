#pragma once

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

class ShaderFactory
{
  public:
	static gpu_ptr<Shader> FromFiles(const std::string& vertexPath,
	                                 const std::string& fragmentPath);
	static gpu_ptr<Shader> FromMemory(const std::string& vertexSrc,
	                                  const std::string& fragmentSrc);

  private:
	static bool ReadFile(const std::string& path, std::string& outContent);
};