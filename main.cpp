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

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		//GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR));
		//GLCALL(glEnable(GL_BLEND));
		GLCALL(glEnable(GL_DEPTH_TEST));

		glm::vec3 position(0.0, 0.0, 0.0);
		float size = 1;

		float wallsCount = 6;
		glm::vec3 wallsNormals[6] = { glm::vec3(0,0,-1),
									 glm::vec3(1,0,0),
									 glm::vec3(0,0,1),
									 glm::vec3(-1,0,0),
									 glm::vec3(0,1,0),
									 glm::vec3(0,-1,0) };



		float buffer[192] = {
				-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //0
				 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //1
				 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //2
				-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //3

				 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //1
				 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //5
				 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //6
				 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //2

				 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //5
				-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //4
				-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //7
				 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //6

				-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //4
				-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //0
				-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //3
				-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //7

				-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //3
				 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //2
				 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //6
				-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //7

				-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //0
				 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //1
				 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //5
				-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //4
		};


		unsigned indices[36] = {
			0,1,3,
			1,2,3,
			4,5,7,
			5,6,7,
			8,9,11,
			9,10,11,
			12,13,15,
			13,14,15,
			16,17,19,
			17,18,19,
			20,21,23,
			21,22,23
		};

		VertexArray va;
		VertexBuffer vb(buffer, 192 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indices, 36);

		Shader shader("Default.shader");
		shader.Bind();

		Texture texture("pobrane.png");
		texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

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
			double time = glfwGetTime();
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
