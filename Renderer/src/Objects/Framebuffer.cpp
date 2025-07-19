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