#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGL/ShaderFactory.h"
#include "OpenGL/VAO.h"
#include "OpenGL/VBO.h"

float triangleVertices[] = {
    // positions        // colors (RGB)
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // red
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // green
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // blue
};

const char* vertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

void main() {
    vColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentSource = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

int main()
{
	Log::Init();

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(
	    800, 600, "Triangle with Interpolation", nullptr, nullptr);
	if (!window)
		return -1;

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	gpu_ptr<Shader> shader =
	    ShaderFactory::FromMemory(vertexSource, fragmentSource);

	gpu_ptr<VAO> vao = make_gpu_ptr<VAO>();
	gpu_ptr<VBO> vbo = make_gpu_ptr<VBO>();
	vao->Load();
	vbo->Load();

	vao->Bind();
	vbo->Bind();
	vbo->SetData(triangleVertices, sizeof(triangleVertices));

	vao->EnableAttribute(0);
	vao->SetAttributePointer<float>(0, 3, 6 * sizeof(float), 0);

	vao->EnableAttribute(1);
	vao->SetAttributePointer<float>(1, 3, 6 * sizeof(float), 3 * sizeof(float));

	vao->Unbind();
	vbo->Unbind();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Bind();
		vao->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao->Unbind();
		shader->Unbind();

		glfwSwapBuffers(window);
	}

	vao->Unload();
	vbo->Unload();
	shader->Unload();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
