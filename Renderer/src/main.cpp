#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Core/Core.h"
#include "Objects/ShaderFactory.h"
#include "Objects/VAO.h"
#include "Objects/VBO.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,
    -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,
    0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f,
    0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
    0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f,
    0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,
    0.0f,  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
    0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  0.5f,  0.5f,
    0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,
    -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
    -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,
    0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f,
    -0.5f, 0.0f,  -1.0f, 0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,
    0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,
    0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,
};

float quadVertices[] = {-1.0f, 1.0f,  0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
                        1.0f,  -1.0f, 1.0f, 0.0f, -1.0f, 1.0f,  0.0f, 1.0f,
                        1.0f,  -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f, 1.0f};

int main()
{
	Core::Init();

	glfwInit();
	GLFWwindow* window =
	    glfwCreateWindow(800, 600, "Renderer", nullptr, nullptr);
	if (!window)
	{
		LOG_CRITICAL("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMaximizeWindow(window);
	LOG_INFO("GLFW window created");
	glfwMakeContextCurrent(window);
	LOG_INFO("Context created");
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	LOG_INFO("ImGui initialized");

	std::unique_ptr<Shader> shader =
	    ShaderFactory::FromFiles("shader/gbuffer.vert", "shader/gbuffer.frag");

	glBindFragDataLocation(shader->GetID(), 0, "gPositionOut");
	glBindFragDataLocation(shader->GetID(), 1, "gNormalOut");
	glBindFragDataLocation(shader->GetID(), 2, "gAlbedoSpecOut");

	auto vao = std::make_unique<VAO>();
	vao->Load();
	vao->Bind();

	auto vbo = std::make_unique<VBO>();
	vbo->Load();
	vbo->Bind();
	vbo->SetData(vertices, sizeof(vertices));

	vao->EnableAttribute(0);
	vao->SetAttributePointer<float>(0, 3, 6 * sizeof(float), 0);
	vao->EnableAttribute(1);
	vao->SetAttributePointer<float>(1, 3, 6 * sizeof(float), 3 * sizeof(float));

	vao->Unbind();
	vbo->Unbind();

	auto compositeShader = ShaderFactory::FromFiles("shader/composite.vert",
	                                                "shader/composite.frag");

	auto quadVAO = std::make_unique<VAO>();
	auto quadVBO = std::make_unique<VBO>();
	quadVAO->Load();
	quadVBO->Load();
	quadVAO->Bind();
	quadVBO->Bind();
	quadVBO->SetData(quadVertices, sizeof(quadVertices));
	quadVAO->EnableAttribute(0);
	quadVAO->SetAttributePointer<float>(0, 2, 4 * sizeof(float), 0);
	quadVAO->EnableAttribute(1);
	quadVAO->SetAttributePointer<float>(1, 2, 4 * sizeof(float),
	                                    2 * sizeof(float));
	quadVAO->Unbind();
	quadVBO->Unbind();

	int SCR_WIDTH, SCR_HEIGHT;
	glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);

	unsigned int gBuffer;
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	unsigned int gPosition, gNormal, gAlbedoSpec;

	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0,
	             GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
	                       gPosition, 0);

	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0,
	             GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
	                       gNormal, 0);

	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
	                       gAlbedoSpec, 0);

	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCR_WIDTH,
	                      SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
	                          GL_RENDERBUFFER, rboDepth);

	unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
	                               GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, attachments);

	float angle = 0.0f;
	float speed = 1.0f;
	float color[3] = {1.0f, 0.5f, 0.2f};
	int displayMode = 1;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Controls");
		ImGui::SliderFloat("Speed", &speed, 0.0f, 5.0f);
		ImGui::ColorEdit3("Color", color);
		ImGui::SliderInt("Display Mode", &displayMode, 1, 4);
		ImGui::Text("1: Final\n2: Position\n3: Normal\n4: Albedo");
		ImGui::End();

		ImGui::Begin("Logs");
		Log::DrawLogs();
		ImGui::End();

		ImGui::Render();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		angle += speed * 0.01f;

		glm::mat4 model =
		    glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat4 view =
		    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 proj = glm::perspective(glm::radians(45.0f),
		                                  width / (float)height, 0.1f, 100.0f);
		glm::mat4 mvp = proj * view * model;

		glm::vec3 lightDir = glm::normalize(glm::vec3(0.5f, 1.0f, 0.3f));

		shader->Bind();
		shader->SetUniformMat4("uMVP", mvp);
		shader->SetUniformVec3("uColor",
		                       glm::vec3(color[0], color[1], color[2]));
		shader->SetUniformMat4("uModel", model);

		vbo->Bind();
		vao->Bind();
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);

		if (displayMode >= 2 && displayMode <= 4)
		{
			switch (displayMode)
			{
			case 2:
				glReadBuffer(GL_COLOR_ATTACHMENT0); // position
				break;
			case 3:
				glReadBuffer(GL_COLOR_ATTACHMENT1); // normal
				break;
			case 4:
				glReadBuffer(GL_COLOR_ATTACHMENT2); // albedo
				break;
			}
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
			                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		else if (displayMode == 1)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			compositeShader->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gPosition);
			compositeShader->SetUniformInt("gPosition", 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, gNormal);
			compositeShader->SetUniformInt("gNormal", 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
			compositeShader->SetUniformInt("gAlbedoSpec", 2);

			quadVAO->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			quadVAO->Unbind();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	vao->Unload();
	quadVAO->Unload();
	vbo->Unload();
	quadVBO->Unload();
	shader->Unload();
	compositeShader->Unload();
	LOG_INFO("Renderer shutdown complete");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}