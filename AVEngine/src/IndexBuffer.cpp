#include "IndexBuffer.h"

#include <glad/glad.h>

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned* data, unsigned count) :
    _count(count) {
    ASSERT(sizeof(unsigned) == sizeof(GLuint));

    GLCall(glCreateBuffers(1, &_rendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &_rendererId));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
}

void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
