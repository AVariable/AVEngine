#include "VertexArray.h"

#include <glad/glad.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glCreateVertexArrays(1, &_rendererId));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &_rendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout) {
	Bind();
	vertexBuffer.Bind();

	const auto& elements = vertexBufferLayout.GetElements();
	unsigned offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements.at(i);
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vertexBufferLayout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(_rendererId));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}
