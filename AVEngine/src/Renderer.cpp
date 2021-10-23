#include "Renderer.h"

#include <cstdio>

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        printf("[OpenGL Error] (%u): %s %s:%i\n", error, function, file, line);
        return false;
    }
    return true;
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}
