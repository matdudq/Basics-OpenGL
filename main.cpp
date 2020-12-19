#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include "Utilities.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "CameraController.h"
#include "CubeGenerator.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
float ASPECT_RATIO = (float)WIDTH / HEIGHT;
constexpr const char* TITLE = "OpenGL";

int main()
{
	{
		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW!" << std::endl;
			return 1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);

		if (!window)
		{
			std::cerr << "Failed to create window!" << std::endl;
			return 1;
		}

		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		if (!gladLoadGL())
		{
			std::cerr << "Failed to create initialize glad!" << std::endl;
			glfwDestroyWindow(window);
			glfwTerminate();
			return 1;
		}

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		GLCALL(glEnable(GL_DEPTH_TEST));

		ShapeData& eggData = GenerateEgg(3.0f,10.0f, 100 );

		VertexArray va;
		VertexBuffer vb(eggData.m_VertexBuffer.data(), eggData.m_VertexBuffer.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(eggData.m_IndexBuffer.data(), eggData.m_IndexBuffer.size());

		Shader shader("Specular_Diffuse.shader");
		shader.Bind();

		Texture texture("pobrane.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;
				
		Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f));
		camera.SetCameraPerspective(65.0f, ASPECT_RATIO);
		CameraController cameraController(camera,*window);
		glm::mat4 model = glm::mat4(1.0f);

		double lastTime = 0;

		while (!glfwWindowShouldClose(window))
		{
			float time = glfwGetTime();
			float deltaTime = time - lastTime;

			cameraController.Update(deltaTime);
		
			renderer.Clear();
			renderer.Draw(va, ib, shader);

			glm::mat4 mvp = camera.GetVPMatirx() * model;
			shader.SetUniformMatrix4f("u_MVP", mvp);
			glm::vec3 cameraPosition = cameraController.GetCameraPosition();

			glm::vec3 lightDir = glm::normalize(glm::vec3(43, 232, 123));
			shader.SetUniform3f("u_CameraPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);
			shader.SetUniform3f("u_LightDir", lightDir.x, lightDir.y, lightDir.z);

			glfwSwapBuffers(window);
			glfwPollEvents();

			lastTime = time;
		}

		glfwDestroyWindow(window);
	}
	glfwTerminate();
	return 0;
}
