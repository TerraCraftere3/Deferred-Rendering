#include "OpenGL/VAO.h"

void VAO::Load()
{
	if (m_ID == 0)
	{
		glGenVertexArrays(1, &m_ID);
		LOG_DEBUG("VAO created with ID: {}", m_ID);
	}
	else
	{
		LOG_WARN("VAO already loaded with ID: {}", m_ID);
	}
}

void VAO::Unload()
{
	if (m_ID != 0)
	{
		glDeleteVertexArrays(1, &m_ID);
		LOG_DEBUG("VAO with ID {} deleted", m_ID);
		m_ID = 0;
	}
}

void VAO::Bind() const { glBindVertexArray(m_ID); }

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::EnableAttribute(GLuint index) const
{
	glEnableVertexAttribArray(index);
}

void VAO::DisableAttribute(GLuint index) const
{
	glDisableVertexAttribArray(index);
}
