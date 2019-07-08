#pragma once

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>


namespace test {
	class TestTexture2d :public Test
	{
	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_proj;
		glm::mat4 m_view;

	public:
		TestTexture2d();
		~TestTexture2d();

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	};

}