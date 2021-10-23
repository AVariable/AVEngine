#pragma once

#include <vector>

#include <glad/glad.h>

#include "Renderer.h"

struct VertexBufferElement {
	static unsigned GetSizeOfType(unsigned type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			default: 
				ASSERT(false);
				return 0;
		}
	}

	unsigned type;
	unsigned count;
	unsigned char normalized;
};

class VertexBufferLayout {
public:
	VertexBufferLayout() :
		_stride(0) {

	}

	template<typename T>
	void Push(unsigned count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned count) {
		_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned>(unsigned count) {
		_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned count) {
		_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return _elements; }
	inline unsigned GetStride() const { return _stride; }

private:
	std::vector<VertexBufferElement> _elements;
	unsigned _stride;
};