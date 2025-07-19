#include "Framebuffer.h"

void Framebuffer::Load()
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	LOG_DEBUG("Framebuffer created with ID: {}", m_ID);
}

void Framebuffer::Unload()
{
	if (m_ID != 0)
	{
		glDeleteFramebuffers(1, &m_ID);
		LOG_DEBUG("Framebuffer with ID: {} deleted", m_ID);
		m_ID = 0;
	}
}

void Framebuffer::Bind(GLuint type) const { glBindFramebuffer(type, m_ID); }

void Framebuffer::Unbind(GLuint type) const { glBindFramebuffer(type, 0); }

void Framebuffer::AttachTexture(const gpu_ptr<Texture>& texture,
                                GLuint attachment, GLuint target)
{
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, target, texture->GetID(),
	                       0);
}

void Framebuffer::AttachTexture(GLuint textureID, GLuint attachment,
                                GLuint target)
{
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, target, textureID, 0);
}

void Framebuffer::AttachRenderbuffer(const gpu_ptr<Renderbuffer>& renderbuffer,
                                     GLuint attachment, GLuint target)
{
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, target,
	                          renderbuffer->GetID());
}

void Framebuffer::AttachRenderbuffer(GLuint renderbufferID, GLuint attachment,
                                     GLuint target)
{
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, target,
	                          renderbufferID);
}