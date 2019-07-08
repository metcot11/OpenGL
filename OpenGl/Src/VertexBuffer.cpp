#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_rendererID));
	//          (Number of buffers, id of the buffer)  
	//Selecting the buffer created above
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	//selecting the buffer created above, tell the compiler that we are using this buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	//alocationg the data to the buffer (Type, size(bits), the buffer(pointer), usage[stream,static or dynamic])
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
