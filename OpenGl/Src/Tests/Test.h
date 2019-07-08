#pragma once
#include <functional>
#include <vector>
#include <string> 

namespace test {
	class Test
	{
	public:
		Test();
		virtual ~Test();

		virtual void OnUpdate(float deltatime);
		virtual void OnRender();
		virtual void OnImGuiRender();

	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& CurrentTestPointer);

		virtual void OnImGuiRender()override;

		template <typename T>
		void RegisterTest(const std::string name)
		{
			std::cout << "Registering Test" << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;

	};
}