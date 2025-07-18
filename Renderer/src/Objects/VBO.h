#pragma once

#include "GPUObject.h"
#include <string>
#include <glm/glm.hpp>

class VBO : public GPUObject
{
public:
    VBO() = default;
    ~VBO() = default;

    void Load() override;
    void Unload() override;

    void Bind() const;
    void Unbind() const;

    template <typename T>
    void SetData(const std::vector<T> &data, GLenum usage = GL_STATIC_DRAW);
    void SetData(const void *data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
    const char *GetClassName() const override { return "VBO"; }
};
