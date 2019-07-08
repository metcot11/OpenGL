#include "Test.h"
#include "imGui/imgui.h"

namespace test {
	Test::Test()
	{
	}
	Test::~Test()
	{
	}
	void Test::OnUpdate(float deltatime)
	{
	}
	void Test::OnRender()
	{
	}
	void Test::OnImGuiRender()
	{
	}


	TestMenu::TestMenu(Test*& CurrentTestPointer)
		:m_CurrentTest(CurrentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}