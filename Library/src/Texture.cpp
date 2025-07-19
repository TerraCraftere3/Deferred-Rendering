#include "OpenGL/Texture.h"

void Texture::Load()
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	LOG_DEBUG("Texture created with ID: {}", m_ID);
}

void Texture::Unload()
{
	if (m_ID != 0)
	{
		glDeleteTextures(1, &m_ID);
		LOG_DEBUG("Texture with ID: {} deleted", m_ID);
		m_ID = 0;
	}
}

void Texture::SetParameter(GLenum pname, GLint param, GLuint target)
{
	Bind(target);
	glBindTexture(target, m_ID);
	glTexParameteri(target, pname, param);
}

void Texture::SetData(GLenum format, GLenum type, const void* data, int width,
                      int height, GLuint target)
{
	Bind(target);
	glTexImage2D(target, 0, format, width, height, 0, format, type, data);
}

void Texture::Bind(GLuint target) const { glBindTexture(target, m_ID); }

void Texture::Unbind(GLuint target) const { glBindTexture(target, 0); }