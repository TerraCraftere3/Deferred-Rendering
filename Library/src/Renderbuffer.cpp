#include "OpenGL/Renderbuffer.h"

void Renderbuffer::Load()
{
	glGenRenderbuffers(1, &m_ID);
	LOG_DEBUG("Renderbuffer created with ID: {}", m_ID);
}

void Renderbuffer::Unload()
{
	glDeleteRenderbuffers(1, &m_ID);
	LOG_DEBUG("Renderbuffer with ID: {} deleted", m_ID);
	m_ID = 0;
}

void Renderbuffer::Bind(GLuint target) const
{
	glBindRenderbuffer(target, m_ID);
}

void Renderbuffer::Unbind(GLuint target) const
{
	glBindRenderbuffer(target, 0);
}

void Renderbuffer::SetData(GLenum internalFormat, GLsizei width, GLsizei height,
                           GLuint target)
{
	Bind(target);
	glRenderbufferStorage(target, internalFormat, width, height);
	Unbind(target);
}
