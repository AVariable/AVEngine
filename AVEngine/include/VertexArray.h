#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);
	void Bind() const;
	void Unbind() const;

private:
	unsigned _rendererId;
};