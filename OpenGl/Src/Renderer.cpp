#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR) {}
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) // creates an GLenum error and sets it equal to the error returnd by the function 
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	//Drawing the triangles using index buffers
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	//                   (Mode, count (number of indices), Type, pointer to the index buffer)
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
