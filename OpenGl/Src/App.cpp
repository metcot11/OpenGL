#include <iostream>
#include <fstream>
//library to open files using c++
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw_gl3.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestTexture.h"


int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(960, 540, "Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();


	test::Test* CurrentTest = nullptr;

	test::TestMenu* testmenu = new test::TestMenu(CurrentTest);
	CurrentTest = testmenu;

	testmenu->RegisterTest<test::TestClearColor>("Clear Color");
	testmenu->RegisterTest<test::TestTexture2d>("Texture2d");



	while (!glfwWindowShouldClose(window))
	{

		renderer.Clear();

		ImGui_ImplGlfwGL3_NewFrame();

		if (CurrentTest)
		{
			CurrentTest->OnUpdate(0.0f);
			CurrentTest->OnRender();
			ImGui::Begin("Test");

			if (CurrentTest != testmenu && ImGui::Button("<-"))
			{
				delete CurrentTest;
				CurrentTest = testmenu;
			}

			CurrentTest->OnImGuiRender();

			ImGui::End();
		}



		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	delete CurrentTest;
	if (CurrentTest != testmenu)
		delete testmenu;
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}