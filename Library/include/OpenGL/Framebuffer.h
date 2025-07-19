#pragma once

#include "GPUObject.h"
#include "Texture.h"
#include "Renderbuffer.h"
#include <string>
#include <glm/glm.hpp>

class Framebuffer : public GPUObject
{
  public:
	Framebuffer() = default;
	~Framebuffer() = default;

	void Load() override;
	void Unload() override;

	void AttachTexture(const gpu_ptr<Texture>& texture, GLuint attachment,
	                   GLuint target = GL_TEXTURE_2D);
	void AttachTexture(GLuint textureID, GLuint attachment,
	                   GLuint target = GL_TEXTURE_2D);

	void AttachRenderbuffer(const gpu_ptr<Renderbuffer>& renderbuffer,
	                        GLuint attachment, GLuint target = GL_RENDERBUFFER);
	void AttachRenderbuffer(GLuint renderbufferID, GLuint attachment,
	                        GLuint target = GL_RENDERBUFFER);

	void Bind(GLuint type = GL_FRAMEBUFFER) const;
	void Unbind(GLuint type = GL_FRAMEBUFFER) const;

	const char* GetClassName() const override { return "Framebuffer"; }

  public:
	static constexpr GLuint READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER;
	static constexpr GLuint DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER;
	static constexpr GLuint DEFAULT = GL_FRAMEBUFFER;
};
