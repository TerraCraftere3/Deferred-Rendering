#include "OpenGL/VBO.h"

void VBO::Load()
{
	glGenBuffers(1, &m_ID);
	LOG_DEBUG("VBO created with ID {}", m_ID);
}

void VBO::Unload()
{
	if (m_ID != 0)
	{
		glDeleteBuffers(1, &m_ID);
		LOG_DEBUG("VBO with ID {} deleted", m_ID);
		m_ID = 0;
	}
}

void VBO::Bind() const
{
	if (m_ID == 0)
	{
		LOG_ERROR("Trying to bind VBO with ID 0");
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::SetData(const void* data, GLsizeiptr size, GLenum usage)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

template <typename T>
void VBO::SetData(const std::vector<T>& data, GLenum usage)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), usage);
}
