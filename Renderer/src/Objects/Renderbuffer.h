#pragma once

#include "GPUObject.h"
#include "Texture.h"
#include <string>
#include <glm/glm.hpp>

class Renderbuffer : public GPUObject
{
  public:
	Renderbuffer() = default;
	~Renderbuffer() = default;

	void Load() override;
	void Unload() override;

	void SetData(GLenum internalFormat, GLsizei width, GLsizei height,
	             GLuint target = GL_RENDERBUFFER);

	void Bind(GLuint target = GL_RENDERBUFFER) const;
	void Unbind(GLuint target = GL_RENDERBUFFER) const;

	const char* GetClassName() const override { return "Renderbuffer"; }

  public:
	static constexpr GLuint DEFAULT = GL_RENDERBUFFER;
};
