#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Renderer.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	//(Number of Vertex arrays, address of the vertex array)
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}


VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		// To set the atrribute to a buffer, it is necesary to enale it first. (index)
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride() , (const void*)offset));
		/*                   (Index,Size,Type,Normalized,Stride,Pointer)
		function that tells the compiler what each value on the buffer means( determines the atributes )*/
	    /*                      Parameters
	   Index : Defining what index the atribute being created is. In this case, we are defining the position of a vertex of
	   a triangule so it starts at the index 0

	   Size : How many of that atribute is stored per vertex. Here it is set to 2 because the position requires 2 values for
	   the X and Y axis

	   Type : Type of the data inside the vertex

	   Normalize(boolian) : Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly
	   as fixed-point values (GL_FALSE) when they are accessed.

	   Stride : Amount of bites in each vertex. It is set to two times the size of a float because there are two floats for
	   each position

	   Pointer : pointer into the atribute, offset of the attribute being defined
	*/
		offset += element.count* VertexBufferElement::GetSizeOfType(element.type);

	}
	

}

