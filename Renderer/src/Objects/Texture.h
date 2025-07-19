#pragma once

#include "GPUObject.h"
#include <string>
#include <glm/glm.hpp>

class Texture : public GPUObject
{
  public:
	Texture() = default;
	~Texture() = default;

	void Load() override;
	void Unload() override;

	void SetParameter(GLenum pname, GLint param, GLuint target = GL_TEXTURE_2D);
	void SetData(GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE,
	             const void* data = nullptr, int width = 0, int height = 0,
	             GLuint target = GL_TEXTURE_2D);

	void Bind(GLuint target = GL_TEXTURE_2D) const;
	void Unbind(GLuint target = GL_TEXTURE_2D) const;

	const char* GetClassName() const override { return "Texture"; }

  public:
	static constexpr GLuint RED = GL_RED;
	static constexpr GLuint RG = GL_RG;
	static constexpr GLuint RGB = GL_RGB;
	static constexpr GLuint BGR = GL_BGR;
	static constexpr GLuint RGBA = GL_RGBA;
	static constexpr GLuint BGRA = GL_BGRA;
	static constexpr GLuint DEPTH_COMPONENT = GL_DEPTH_COMPONENT;
	static constexpr GLuint STENCIL_INDEX = GL_STENCIL_INDEX;
	static constexpr GLuint DEPTH_STENCIL = GL_DEPTH_STENCIL;
	// ... Rest is just OpenGL Types

	static constexpr GLuint MIN_FILTER = GL_TEXTURE_MIN_FILTER;
	static constexpr GLuint MAG_FILTER = GL_TEXTURE_MAG_FILTER;
	static constexpr GLuint WRAP_S = GL_TEXTURE_WRAP_S;
	static constexpr GLuint WRAP_T = GL_TEXTURE_WRAP_T;
	static constexpr GLuint WRAP_R = GL_TEXTURE_WRAP_R;

	static constexpr GLuint NEAREST = GL_NEAREST;
	static constexpr GLuint LINEAR = GL_LINEAR;
	static constexpr GLuint NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST;
	static constexpr GLuint LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST;

	static constexpr GLuint TEXTURE_1D = GL_TEXTURE_1D;
	static constexpr GLuint TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY;
	static constexpr GLuint TEXTURE_2D = GL_TEXTURE_2D;
	static constexpr GLuint TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY;
	static constexpr GLuint TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE;
	static constexpr GLuint TEXTURE_3D = GL_TEXTURE_3D;
	static constexpr GLuint TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE;
	static constexpr GLuint TEXTURE_BUFFER = GL_TEXTURE_BUFFER;
	static constexpr GLuint TEXTURE_CUBE = GL_TEXTURE_CUBE_MAP;
};
