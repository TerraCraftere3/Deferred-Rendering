#pragma once

#include <glm/glm.hpp>
#include <string>

#include "GPUObject.h"

template <typename T> struct GLTypeTraits;

template <> struct GLTypeTraits<float>
{
	static constexpr GLenum type = GL_FLOAT;
};

template <> struct GLTypeTraits<int>
{
	static constexpr GLenum type = GL_INT;
};

template <> struct GLTypeTraits<unsigned int>
{
	static constexpr GLenum type = GL_UNSIGNED_INT;
};

class VAO : public GPUObject
{
  public:
	VAO() = default;
	~VAO() = default;

	void Load() override;
	void Unload() override;

	void Bind() const;
	void Unbind() const;

	void EnableAttribute(GLuint index) const;
	void DisableAttribute(GLuint index) const;

	template <typename T>
	void SetAttributePointer(GLuint index, GLint count, GLsizei stride,
	                         std::size_t offset,
	                         GLboolean normalized = GL_FALSE) const
	{
		static_assert(
		    std::is_same_v<T, float> || std::is_same_v<T, int> ||
		        std::is_same_v<T, unsigned int>,
		    "Unsupported attribute type. Please specialize GLTypeTraits "
		    "for this type.");

		glVertexAttribPointer(index, count, GLTypeTraits<T>::type, normalized,
		                      stride, reinterpret_cast<const void*>(offset));
	}

	const char* GetClassName() const override { return "VAO"; }

  private:
	GLuint m_CurrentAttribute = 0;
	std::size_t m_Stride = 0;
};
