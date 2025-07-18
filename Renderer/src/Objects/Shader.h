#pragma once

#include "GPUObject.h"
#include <string>
#include <glm/glm.hpp>

class Shader : public GPUObject
{
public:
    Shader() = default;
    ~Shader() = default;

    void SetSources(const std::string &vertexSrc, const std::string &fragmentSrc);
    void Load() override;
    void Unload() override;

    void Bind() const;
    void Unbind() const;

    void SetUniformInt(const std::string &name, int value);
    void SetUniformFloat(const std::string &name, float value);
    void SetUniformVec2(const std::string &name, const glm::vec2 &value);
    void SetUniformVec3(const std::string &name, const glm::vec3 &value);
    void SetUniformVec4(const std::string &name, const glm::vec4 &value);
    void SetUniformMat3(const std::string &name, const glm::mat3 &matrix);
    void SetUniformMat4(const std::string &name, const glm::mat4 &matrix);

    const char *GetClassName() const override { return "Shader"; }

private:
    std::string m_VertexSource;
    std::string m_FragmentSource;

    bool CheckCompileErrors(GLuint shader, const std::string &type);
    bool CheckLinkErrors(GLuint program);
};
