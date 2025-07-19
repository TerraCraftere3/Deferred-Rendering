#pragma once

#include "GPUObject.h"
#include <string>
#include <glm/glm.hpp>

class Framebuffer : public GPUObject
{
  public:
	Framebuffer() = default;
	~Framebuffer() = default;

	void Load() override;
	void Unload() override;

	void Bind(GLuint type = GL_FRAMEBUFFER) const;
	void Unbind(GLuint type = GL_FRAMEBUFFER) const;

	const char* GetClassName() const override { return "Framebuffer"; }

  public:
	static const GLuint READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER;
	static const GLuint DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER;
	static const GLuint DEFAULT = GL_FRAMEBUFFER;
};
