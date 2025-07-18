#include "Shader.h"
#include "VBO.h"

void Shader::SetSources(const std::string& vertexSrc,
                        const std::string& fragmentSrc)
{
	m_VertexSource = vertexSrc;
	m_FragmentSource = fragmentSrc;
}

void Shader::Load()
{
	// ==== Vertex Shader ====
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSrc = m_VertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);
	if (!CheckCompileErrors(vertexShader, "VERTEX"))
	{
		glDeleteShader(vertexShader);
		return;
	}

	// ==== Fragment Shader ====
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSrc = m_FragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);
	if (!CheckCompileErrors(fragmentShader, "FRAGMENT"))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	// ==== Shader Program ====
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	if (!CheckLinkErrors(program))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(program);
		return;
	}

	// ==== Reset ====
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (m_ID != 0)
	{
		LOG_WARN("Shader already loaded, unloading previous shader!!! (NOT "
		         "RECOMMENDED)");
		Unload();
	}

	m_ID = program;
	LOG_DEBUG("Shader created with ID {}", m_ID);
}

void Shader::Unload()
{
	if (m_ID != 0)
	{
		glDeleteProgram(m_ID);
		m_ID = 0;
	}
}

void Shader::Bind() const { glUseProgram(m_ID); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetUniformInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetUniformFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetUniformVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE,
	                   &matrix[0][0]);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE,
	                   &matrix[0][0]);
}

bool Shader::CheckCompileErrors(GLuint shader, const std::string& type)

{
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		LOG_ERROR("Shader ({}) failed to compile: {}\n", type, infoLog);
		return false;
	}
	return true;
}

bool Shader::CheckLinkErrors(GLuint program)
{
	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, nullptr, infoLog);
		LOG_ERROR("Shader program failed to link: {}\n", infoLog);
		return false;
	}
	return true;
}