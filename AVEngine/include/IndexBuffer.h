#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned* data, unsigned count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned GetCount() const { return _count; }

private:
	unsigned _rendererId;
	unsigned _count;
};